pdfl=`cat /home/nlevisrael/gits/ntxh/wip-sebi/ar/../preferred/preferred-latex`
echo $pdfl
$pdfl -synctex=1 -interaction=nonstopmode --shell-escape -output-dir=out  pr.tex

 
