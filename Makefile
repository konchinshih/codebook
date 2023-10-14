.PHONY: all
all: main.pdf

main.pdf: main.tex code/**
	xelatex -shell-escape main.tex
	xelatex -shell-escape main.tex
	rm -rf _minted-main main.aux main.bbl main.bcf main.blg main.log main.nav main.out main.run.xml main.snm main.toc main.vrb

.PHONY: clean
clean:
	rm -rf main.pdf _minted-main main.aux main.bbl main.bcf main.blg main.log main.nav main.out main.run.xml main.snm main.toc main.vrb
