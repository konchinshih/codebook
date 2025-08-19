FROM pandoc/extra:3.7-alpine

RUN apk add texlive-full font-noto font-noto-cjk biber make unzip \
      python3 py3-pygments curl
#RUN apk add biber make unzip python3 py3-pygments curl

RUN mkdir ttf-dmcasansserif && cd ttf-dmcasansserif && \
      curl -L -O 'https://typedesign.replit.app/DMCAsansserif9.0-20252.zip' && \
      unzip 'DMCAsansserif9.0-20252.zip' && \
      ls | grep .ttf | xargs -I% -n1 install -Dm644 % /usr/share/fonts/TTF/% && \
      cd - && rm -rf ttf-dmcasansserif

WORKDIR /work
ENV PATH="/usr/bin/vendor_perl:${PATH}"
ENTRYPOINT ["sh", "-c"]
CMD ["make"]
