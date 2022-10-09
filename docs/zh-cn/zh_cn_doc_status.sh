#! /bin/sh
#
# Script to display Simplified Chinese translation status of documents
# Copied from the japanese one
#
if [ ! -d docs/zh-cn ]; then
    echo "'docs/zh-cn' not found."
    echo "do:"
    echo "  cd \$(QMK_TOP)"
    echo "  ./docs/zh-cn/zh-cn_doc_status.sh"
    exit 1
fi

en_docs=`cd docs;ls -1 [a-z]*.md`
zh_cn_docs=`cd docs/zh-cn;ls -1 [a-z]*.md`
en_count=`echo $en_docs | wc -w`
zh_cn_count=`echo $zh_cn_docs | wc -w`
echo "English documents  $en_count files."
echo "Simplified Chinese documents $zh_cn_count files."

echo "Files that have not been translated yet:"
for docfile in $en_docs
do
    if [ ! -f docs/zh-cn/$docfile ]; then
        wc docs/$docfile
    fi
done | sort
echo "Files that have not been updated yet:"
grep --no-filename "^[ ]*git diff" docs/zh-cn/*.md | while read cmd
do
  cline=`echo $cmd | sh | wc -l`
  if [ $cline -gt 0 ]; then
    echo "$cline $cmd"
 fi
done | sort
