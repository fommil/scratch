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
dvips -t a4 "Sam Halliday, Masters Thesis" -o main.ps > /dev/null 2>&1 &&
echo "Squeezing 2 pages into an A4"
psnup -2 -pa4 main.ps draft.ps > /dev/null 2>&1 &&
rm main.ps "Sam Halliday, Masters Thesis" *.log *.aux *.toc
echo "Finished, outputted file is"
ls -sh draft.ps
