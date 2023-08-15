
trap 'echo "# $BASH_COMMAND"' DEBUG 

HUB=`cat ./user-specific/hub`

echo "pushing: ${HUB}"

docker push ${HUB}

