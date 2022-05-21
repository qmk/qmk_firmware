#! /bin/sh
#
# Script to display the Japanese translation status of documents
#
if [ ! -d docs/ja ]; then
    echo "'docs/ja' not found."
    echo "do:"
    echo "  cd \$(QMK_TOP)"
    echo "  ./docs/ja/ja_doc_status.sh"
    exit 1
fi

en_docs=`cd docs;ls -1 [a-z]*.md`
ja_docs=`cd docs/ja;ls -1 [a-z]*.md`
en_count=`echo $en_docs | wc -w`
ja_count=`echo $ja_docs | wc -w`
echo "English documents  $en_count files."
echo "Japanese documents $ja_count files."

echo "Files that have not been translated yet:"
for docfile in $en_docs
do
    if [ ! -f docs/ja/$docfile ]; then
        wc docs/$docfile
    fi
done | sort
echo "Files that have not been updated yet:"
grep --no-filename "^[ ]*git diff" docs/ja/*.md | while read cmd
do
  cline=`echo $cmd | sh | wc -l`
  if [ $cline -gt 0 ]; then
    echo "$cline $cmd"
 fi
done | sort
