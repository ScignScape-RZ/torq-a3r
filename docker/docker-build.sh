trap 'echo "# $BASH_COMMAND"' DEBUG
DOCKER_BUILDKIT=1 docker build --no-cache=true -t axiatropicsemantics/torq-a3r-dev .
