set -e

git fetch origin

git checkout stg

git pull origin stg

git merge origin/dev

TAG="stg-$(date +%Y%m%d-%H%M%S)"

git tag $TAG

git push origin stg

git push origin $TAG

echo "Merge dev → stg completed. Tag: $TAG"