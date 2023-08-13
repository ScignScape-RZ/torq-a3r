trap 'echo "# $BASH_COMMAND"' DEBUG

HUB=`cat ./user-specific/hub`

echo "building: ${HUB}"

DOCKER_BUILDKIT=1 docker build --no-cache=true -t axiatropicsemantics/torq-a3r-dev ../..
