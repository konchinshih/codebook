.PHONY: all docker typst latex clean distclean

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

main.pdf: typst

typst: main.typ hash.sha256 code/**
	python3 make-palette.py
	typst compile main.typ main.pdf --font-path fonts --creation-timestamp 0

hash.sha256: hash.sh code/**
	./hash.sh

latex: main.tex code/**
	xelatex -shell-escape main.tex
	xelatex -shell-escape main.tex
	-rm -rf $(INTERMEDIATE_FILES)

endif

clean:
	-rm -rf $(INTERMEDIATE_FILES)

distclean:
	-rm -rf main.pdf hash.sha256 $(INTERMEDIATE_FILES)
