#!/bin/sh

# Run the internal tests of nftables (shell)

# The testsuite requires kernel at least 4.x
if [ "$(uname -r | cut -d. -f1)" -lt 4 ] ; then
	echo "W: this testsuite is likely to produce many fails because of old kernel"
fi

set -e
cd tests/shell
./run-tests.sh -v
