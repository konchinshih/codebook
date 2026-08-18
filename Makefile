.PHONY: all clean docker fast typst

DOCKER_IMAGE ?= ghcr.io/konchinshih/codebook:main
DOCKER_MAKE_GOALS := $(filter-out docker,$(MAKECMDGOALS))

INTERMEDIATE_FILES += _minted-main main.aux main.bbl main.bcf main.blg \
											main.log main.nav main.out main.run.xml main.snm \
											main.toc main.vrb missfont.log

all: main.pdf

docker:
	docker run \
		-v ".:/work" --rm \
		-u "$(shell id -u):$(shell id -g)" \
		--platform=linux/amd64 \
		--entrypoint make \
		$(DOCKER_IMAGE) $(DOCKER_MAKE_GOALS)

ifneq ($(filter docker,$(MAKECMDGOALS)),)
ifneq ($(strip $(DOCKER_MAKE_GOALS)),)
$(DOCKER_MAKE_GOALS):
	@:
endif
else
typst:
	python3 make-palette.py && typst compile main.typ main.pdf --font-path fonts
endif

main.pdf: main.tex code/**
	xelatex -shell-escape main.tex
	xelatex -shell-escape main.tex
	-rm -rf $(INTERMEDIATE_FILES)

fast:
	xelatex --shell-escape main.tex
	xelatex --shell-escape main.tex

clean:
	-rm -rf main.pdf $(INTERMEDIATE_FILES)
