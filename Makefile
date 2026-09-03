.PHONY: all docker typst latex clean distclean

DOCKER_IMAGE ?= ghcr.io/konchinshih/codebook:main
DOCKER_MAKE_GOALS := $(filter-out docker,$(MAKECMDGOALS))
# Rootless Podman remaps the bind-mounted working dir to root inside its user
# namespace, so the -u UID:GID process below can't write to it (e.g. the
# make-palette.py tempfile in themes/) unless we ask Podman to keep the
# caller's UID mapped 1:1. Real Docker doesn't understand --userns=keep-id
# (and doesn't need it), so only add it when the `docker` binary is Podman.
DOCKER_USERNS := $(if $(findstring podman,$(shell docker --version 2>&1)),--userns=keep-id,)

INTERMEDIATE_FILES += _minted-main main.aux main.bbl main.bcf main.blg \
											main.log main.nav main.out main.run.xml main.snm \
											main.toc main.vrb missfont.log

all: main.pdf

docker:
	docker run \
		-v ".:/work" --rm \
		-u "$(shell id -u):$(shell id -g)" \
		$(DOCKER_USERNS) \
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
	typst compile main.typ main.pdf --font-path fonts --ignore-system-fonts --creation-timestamp 0

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
