clear
echo "Cleaning Directory"
rm *.ps *.dvi *.log *.aux *.toc > /dev/null 2>&1
echo "Running LaTeX"
latex main.tex > /dev/null &&
echo "Running LaTeX again"
latex main.tex > /dev/null &&
echo "Running LaTeX AGAIN, to make sure references are all OK"
latex main.tex > /dev/null &&
mv main.dvi "Sam Halliday, Masters Thesis"
echo "Making PS file"
dvips -t a4 "Sam Halliday, Masters Thesis" -o masters.ps > /dev/null 2>&1 &&
gzip -9 masters.ps
/bin/mv masters.ps.gz masters.ps
echo "Making PDF file"
dvipdf "Sam Halliday, Masters Thesis" masters.pdf > /dev/null 2>&1 &&
echo "Cleaning up"
rm "Sam Halliday, Masters Thesis" *.log *.aux *.toc
echo "Finished, outputted file is"
ls -sh masters.ps
