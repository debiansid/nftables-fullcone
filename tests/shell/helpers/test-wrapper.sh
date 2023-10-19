#!/bin/bash -e

# This wrapper wraps the invocation of the test. It is called by run-tests.sh,
# and already in the unshared namespace.
#
# For some printf debugging, you can also patch this file.

array_contains() {
	local needle="$1"
	local a
	shift
	for a; do
		[ "$a" = "$needle" ] && return 0
	done
	return 1
}

TEST="$1"
TESTBASE="$(basename "$TEST")"
TESTDIR="$(dirname "$TEST")"

START_TIME="$(cut -d ' ' -f1 /proc/uptime)"

export TMPDIR="$NFT_TEST_TESTTMPDIR"

CLEANUP_UMOUNT_VAR_RUN=n

cleanup() {
	if [ "$CLEANUP_UMOUNT_VAR_RUN" = y ] ; then
		umount "/var/run" &>/dev/null || :
	fi
}

trap cleanup EXIT

printf '%s\n' "$TEST" > "$NFT_TEST_TESTTMPDIR/name"

read tainted_before < /proc/sys/kernel/tainted

if [ "$NFT_TEST_HAS_UNSHARED_MOUNT" = y ] ; then
	# We have a private mount namespace. We will mount /var/run/ as a tmpfs.
	#
	# The main purpose is so that we can create /var/run/netns, which is
	# required for `ip netns add` to work.  When running as rootless, this
	# is necessary to get such tests to pass. When running rootful, it's
	# still useful to not touch the "real" /var/run/netns of the system.
	#
	# Note that this also hides everything that might reside in /var/run.
	# That is desirable, as tests should not depend on content there (or if
	# they do, we need to explicitly handle it as appropriate).
	if mount -t tmpfs --make-private "/var/run" ; then
		CLEANUP_UMOUNT_VAR_RUN=y
	fi
	mkdir -p /var/run/netns
fi

TEST_TAGS_PARSED=0
ensure_TEST_TAGS() {
	if [ "$TEST_TAGS_PARSED" = 0 ] ; then
		TEST_TAGS_PARSED=1
		TEST_TAGS=( $(sed -n '1,10 { s/^.*\<\(NFT_TEST_REQUIRES\|NFT_TEST_SKIP\)\>\s*(\s*\(NFT_TEST_SKIP_[a-zA-Z0-9_]\+\|NFT_TEST_HAVE_[a-zA-Z0-9_]\+\)\s*).*$/\1(\2)/p }' "$1" 2>/dev/null || : ) )
	fi
}

rc_test=0

if [ "$rc_test" -eq 0 ] ; then
	for KEY in $(compgen -v | grep '^NFT_TEST_HAVE_') ; do
		if [ "${!KEY}" != n ]; then
			continue
		fi
		ensure_TEST_TAGS "$TEST"
		if array_contains "NFT_TEST_REQUIRES($KEY)" "${TEST_TAGS[@]}" ; then
			echo "Test skipped due to $KEY=n (test has \"NFT_TEST_REQUIRES($KEY)\" tag)" >> "$NFT_TEST_TESTTMPDIR/testout.log"
			rc_test=77
			break
		fi
	done
fi

if [ "$rc_test" -eq 0 ] ; then
	for KEY in $(compgen -v | grep '^NFT_TEST_SKIP_') ; do
		if [ "${!KEY}" != y ]; then
			continue
		fi
		ensure_TEST_TAGS "$TEST"
		if array_contains "NFT_TEST_SKIP($KEY)" "${TEST_TAGS[@]}" ; then
			echo "Test skipped due to $KEY=y (test has \"NFT_TEST_SKIP($KEY)\" tag)" >> "$NFT_TEST_TESTTMPDIR/testout.log"
			rc_test=77
			break
		fi
	done
fi

if [ "$rc_test" -eq 0 ] ; then
	"$TEST" &>> "$NFT_TEST_TESTTMPDIR/testout.log" || rc_test=$?
fi

$NFT list ruleset > "$NFT_TEST_TESTTMPDIR/ruleset-after"

read tainted_after < /proc/sys/kernel/tainted

DUMPPATH="$TESTDIR/dumps"
DUMPFILE="$DUMPPATH/$TESTBASE.nft"
NODUMPFILE="$DUMPPATH/$TESTBASE.nodump"

dump_written=

# The caller can request a re-geneating of the dumps, by setting
# DUMPGEN=y.
#
# This only will happen if the command completed with success.
#
# It also will only happen for tests, that have a "$DUMPPATH" directory. There
# might be tests, that don't want to have dumps created. The existence of the
# directory controls that. Tests that have a "$NODUMPFILE" file, don't get a dump generated.
if [ "$rc_test" -eq 0 -a "$DUMPGEN" = y -a -d "$DUMPPATH" -a ! -f "$NODUMPFILE" ] ; then
	dump_written=y
	if [ ! -f "$DUMPFILE" ] ; then
		# No dumpfile exists yet. We generate both a .nft and a .nodump
		# file. The user can pick which one to commit to git.
		: > "$NODUMPFILE"
	fi
	cat "$NFT_TEST_TESTTMPDIR/ruleset-after" > "$DUMPFILE"
fi

rc_dump=0
if [ "$rc_test" -ne 77 -a -f "$DUMPFILE" ] ; then
	if [ "$dump_written" != y ] ; then
		if ! $DIFF -u "$DUMPFILE" "$NFT_TEST_TESTTMPDIR/ruleset-after" &> "$NFT_TEST_TESTTMPDIR/ruleset-diff" ; then
			rc_dump=1
		else
			rm -f "$NFT_TEST_TESTTMPDIR/ruleset-diff"
		fi
	fi
fi
if [ "$rc_dump" -ne 0 ] ; then
	echo "$DUMPFILE" > "$NFT_TEST_TESTTMPDIR/rc-failed-dump"
fi

rc_chkdump=0
# check that a flush after the test succeeds. We anyway need a clean ruleset
# for the `nft --check` next.
$NFT flush ruleset &> "$NFT_TEST_TESTTMPDIR/rc-failed-chkdump" || rc_chkdump=1
if [ -f "$DUMPFILE" ] ; then
	# We have a dumpfile. Call `nft --check` to possibly cover new code
	# paths.
	if [ "$rc_test" -eq 77 ] ; then
		# The test was skipped. Possibly we don't have the required
		# features to process this file. Ignore any output and exit
		# code, but still call the program (for valgrind or sanitizer
		# issue we hope to find).
		$NFT --check -f "$DUMPFILE" &>/dev/null || :
	else
		$NFT --check -f "$DUMPFILE" &>> "$NFT_TEST_TESTTMPDIR/rc-failed-chkdump" || rc_chkdump=1
	fi
fi
if [ -s "$NFT_TEST_TESTTMPDIR/rc-failed-chkdump" ] ; then
	# Non-empty output? That is wrong.
	rc_chkdump=1
elif [ "$rc_chkdump" -eq 0 ] ; then
	rm -rf "$NFT_TEST_TESTTMPDIR/rc-failed-chkdump"
fi
if [ "$rc_chkdump" -ne 0 ] ; then
	# Ensure we don't have empty output files. Always write something, so
	# that `grep ^ -R` lists the file.
	echo -e "<<<<<\n\nCalling \`nft --check\` (or \`nft flush ruleset\`) failed for \"$DUMPFILE\"" >> "$NFT_TEST_TESTTMPDIR/rc-failed-chkdump"
fi

rc_valgrind=0
[ -f "$NFT_TEST_TESTTMPDIR/rc-failed-valgrind" ] && rc_valgrind=1

rc_tainted=0
if [ "$tainted_before" != "$tainted_after" ] ; then
	echo "$tainted_after" > "$NFT_TEST_TESTTMPDIR/rc-failed-tainted"
	rc_tainted=1
fi

if [ "$rc_valgrind" -ne 0 ] ; then
	rc_exit=122
elif [ "$rc_tainted" -ne 0 ] ; then
	rc_exit=123
elif [ "$rc_test" -ge 118 -a "$rc_test" -le 124 ] ; then
	# Special exit codes are reserved. Coerce them.
	rc_exit=125
elif [ "$rc_test" -ne 0 ] ; then
	rc_exit="$rc_test"
elif [ "$rc_dump" -ne 0 ] ; then
	rc_exit=124
elif [ "$rc_chkdump" -ne 0 ] ; then
	rc_exit=121
else
	rc_exit=0
fi


# We always write the real exit code of the test ($rc_test) to one of the files
# rc-{ok,skipped,failed}, depending on which it is.
#
# Note that there might be other rc-failed-{dump,tainted,valgrind} files with
# additional errors. Note that if such files exist, the overall state will
# always be failed too (and an "rc-failed" file exists).
#
# On failure, we also write the combined "$rc_exit" code from "test-wrapper.sh"
# to "rc-failed-exit" file.
#
# This means, failed tests will have a "rc-failed" file, and additional
# "rc-failed-*" files exist for further information.
if [ "$rc_exit" -eq 0 ] ; then
	RC_FILENAME="rc-ok"
elif [ "$rc_exit" -eq 77 ] ; then
	RC_FILENAME="rc-skipped"
else
	RC_FILENAME="rc-failed"
	echo "$rc_exit" > "$NFT_TEST_TESTTMPDIR/rc-failed-exit"
fi
echo "$rc_test" > "$NFT_TEST_TESTTMPDIR/$RC_FILENAME"

END_TIME="$(cut -d ' ' -f1 /proc/uptime)"
WALL_TIME="$(awk -v start="$START_TIME" -v end="$END_TIME" "BEGIN { print(end - start) }")"
printf "%s\n" "$WALL_TIME" "$START_TIME" "$END_TIME" > "$NFT_TEST_TESTTMPDIR/times"

exit "$rc_exit"
