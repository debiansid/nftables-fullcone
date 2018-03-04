if BUILD_MAN
man_MANS = nft.8
endif

if BUILD_PDF
pdf_DATA = nft.pdf
endif

pdfdir=${docdir}/pdf

BUILD_DATE=$(shell dpkg-parsechangelog -l../debian/changelog -S Date | LC_ALL=C date -u "+%d %B %Y" -f -)

.xml.pdf:
	${AM_V_GEN}dblatex -q -t pdf -o $@ $<

.xml.8:
	${AM_V_GEN}${DB2MAN} --string-param header-3="$(BUILD_DATE)" --xinclude $<

EXTRA_DIST = nft.xml

CLEANFILES = nft.pdf nft.8 *~
