#!/bin/bash

gziptocdata() {
  cd web/pages
  for f in $(find . -type f | sort); do
    pagepath="${f##.}"
    pagesuffix="${pagepath##*.}"
    pathsha1="page_$(echo ${pagepath} | sha1sum | cut -c-40)"
    echo "const $(gzip -9nc ${f} | xxd -i -name ${pathsha1} | grep -ve "_len")"
    echo
    pagestruct="${pagestruct}{\"${pagepath}\", "mime_${pagesuffix}", ${pathsha1}, sizeof(${pathsha1})},\n"
  done

}

geninclude() {
  echo '#include "html.pages.struct.h"'
  echo
  gziptocdata
  echo
  echo 'const PAGE_DATA pagedata[] = {'
  echo -ne "${pagestruct}"
  echo '};'
}

if [ "${1}" = "-d" ]; then
  geninclude
else
  geninclude >src/html.pages.data.h
fi
