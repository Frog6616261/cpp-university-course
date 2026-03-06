set -e

git fetch origin

git checkout prd

git pull origin prd

git merge origin/stg

TAG="prd-$(date +%Y%m%d-%H%M%S)"

git tag $TAG

git push origin prd

git push origin $TAG

echo "Merge stg → prd completed. Tag: $TAG"