FROM archlinux:latest

RUN pacman -Syu --noconfirm texlive-basic texlive-latex texlive-latexrecommended texlive-latexextra \
    texlive-xetex texlive-pictures texlive-mathscience texlive-bibtexextra \
    texlive-fontsrecommended texlive-fontutils \
    texlive-langcjk texlive-langchinese noto-fonts noto-fonts-cjk \
    biber minted make unzip

RUN mkdir ttf-dmcasansserif && cd ttf-dmcasansserif && \
    curl -L -O 'https://typedesign.repl.co/DMCAsansserif9.0-20252.zip' && \
    unzip 'DMCAsansserif9.0-20252.zip' && \
    ls | grep .ttf | xargs -I% -n1 install -Dm644 % /usr/share/fonts/TTF/% && \
    cd - && rm -rf ttf-dmcasansserif

WORKDIR /work
ENV PATH="/usr/bin/vendor_perl:${PATH}"
CMD ["make"]
