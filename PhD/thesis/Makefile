all: main.dvi

main.dvi: *.tex
	latex main.tex
	latex main.tex
	latex main.tex

pdf: *.tex
	pdflatex main.tex
	pdflatex main.tex
	pdflatex main.tex

ps: main.dvi
	dvips main.dvi -o main.ps

clean:
	rm -f  *.dvi *.log *.aux *.toc *.bak \#*\# _region_.tex
	rm -f  *.bbl *.blg *~ *.ini
	rm -rf *.prv auto
