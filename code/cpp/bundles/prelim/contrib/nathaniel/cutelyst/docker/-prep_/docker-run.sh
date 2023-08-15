trap 'echo "# $BASH_COMMAND"' DEBUG

HUB=`cat ./user-specific/hub`

echo "running: ${HUB}"

docker run -p 127.0.0.1:20198:20199 -it ${HUB} 


