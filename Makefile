.PHONY: all clean docker

INTERMEDIATE_FILES += _minted-main main.aux main.bbl main.bcf main.blg \
											main.log main.nav main.out main.run.xml main.snm \
											main.toc main.vrb missfont.log

all: main.pdf

docker:
	docker build --platform=linux/amd64 -t latex .
	docker run --platform=linux/amd64 -v ".:/work" --rm -u "$(shell id -u):$(shell id -g)" latex

main.pdf: main.tex code/**
	xelatex -shell-escape main.tex
	xelatex -shell-escape main.tex
	-rm -rf $(INTERMEDIATE_FILES)

clean:
	-rm -rf main.pdf $(INTERMEDIATE_FILES)
