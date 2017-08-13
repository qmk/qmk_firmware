#/bin/bash
# {
#     "name": "Planck",
#     "shortname": "planck"
# }
printf "[" > keyboards.json
for project in $(find . -regex '\./keyboards/[a-z0-9_\-]+/config.h')
do
    shortname=$(printf $project | sed -r "s/\.\/keyboards\/([a-zA-Z0-9_\-]+).*/\1/g")
    subprojects=$(find . -regex "\./keyboards/$shortname/[a-z0-9_\-]+/readme.md" | grep -vwE "keymaps")
    if [ -z "$subprojects" ]; then
        readme=$(find . -regex "\./keyboards/$shortname/readme.md")
        if [ -z $readme ]; then
            name=$shortname
        else
            name=$(head -n 1 $readme | sed -r "s/# //")
        fi
        # https://stackoverflow.com/questions/2390199/finding-the-date-time-a-file-was-first-added-to-a-git-repository
        date_added=$(git log --diff-filter=A --follow --format=%aI -- keyboards/$shortname | tail -1)
        printf "
  {
    \"name\": \"%s\",
    \"shortname\": \"%s\",
    \"date_added\": \"%s\"
  }," "$name" "$shortname" "$date_added" >> keyboards.json
    else
        for subproject in $subprojects
        do
            subproject_name=$(printf $subproject | sed -r "s/\.\/keyboards\/${shortname}\/([a-zA-Z0-9_\-]+).*/\1/g")
            readme=$(find . -regex "\./keyboards/$shortname/$subproject_name/readme.md")
            if [ -z $readme ]; then
                name=$shortname
            else
                name=$(head -n 1 $readme | sed -r "s/# //")
            fi
        # https://stackoverflow.com/questions/2390199/finding-the-date-time-a-file-was-first-added-to-a-git-repository
            date_added=$(git log --diff-filter=A --follow --format=%aI -- keyboards/$shortname/$subproject_name | tail -1)
            printf "
  {
    \"name\": \"%s\",
    \"shortname\": \"%s-%s\",
    \"date_added\": \"%s\"
  }," "$name" "$shortname" "$subproject_name" "$date_added" >> keyboards.json
        done        
    fi
done
printf "
]" >> keyboards.json