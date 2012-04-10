dummy:

install:
	mkdir -p ${DESTDIR}/etc/ld.so.conf.d
	install -m644 ncore.conf ${DESTDIR}/etc/ld.so.conf.d/ncore.conf
	mkdir -p ${DESTDIR}/home/y/lib
	install -m755 libncore.so.1 ${DESTDIR}/home/y/lib/libncore.so.1
	ln -s libncore.so.1 ${DESTDIR}/home/y/lib/libncore.so
	mkdir -p ${DESTDIR}/home/y/include/ncore
	install -m644 str_util.h ${DESTDIR}/home/y/include/ncore/str_util.h
	install -m644 uni_util.h ${DESTDIR}/home/y/include/ncore/uni_util.h
	install -m644 base64.h ${DESTDIR}/home/y/include/ncore/base64.h
	install -m644 url_codec.h ${DESTDIR}/home/y/include/ncore/url_codec.h
