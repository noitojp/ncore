dummy:

install:
	mkdir -p ${DESTDIR}/etc/ld.so.conf.d
	install -m644 ncore.conf ${DESTDIR}/etc/ld.so.conf.d/ncore.conf
	mkdir -p ${DESTDIR}/home/z/lib
	install -m755 libncore.so.1 ${DESTDIR}/home/z/lib/libncore.so.1
	ln -s libncore.so.1 ${DESTDIR}/home/z/lib/libncore.so
	mkdir -p ${DESTDIR}/home/z/include/ncore
	install -m644 str_util.h ${DESTDIR}/home/z/include/ncore/str_util.h
	install -m644 uni_util.h ${DESTDIR}/home/z/include/ncore/uni_util.h
	install -m644 base64.h ${DESTDIR}/home/z/include/ncore/base64.h
	install -m644 url_codec.h ${DESTDIR}/home/z/include/ncore/url_codec.h
