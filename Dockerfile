FROM pandoc/extra:3.7-alpine

RUN apk add --no-cache texlive-full font-noto font-noto-cjk biber make typst unzip \
      python3 py3-pygments curl

RUN apk add --no-cache xz

ARG TYPST_VERSION=0.15.1

RUN curl --fail --location --retry 3 \
      --output /tmp/typst.tar.xz \
      "https://github.com/typst/typst/releases/download/v${TYPST_VERSION}/typst-x86_64-unknown-linux-musl.tar.xz" && \
      tar -xJf /tmp/typst.tar.xz -C /tmp && \
      install -Dm755 "/tmp/typst-x86_64-unknown-linux-musl/typst" /usr/local/bin/typst && \
      rm -rf /tmp/typst.tar.xz "/tmp/typst-x86_64-unknown-linux-musl"

RUN mkdir ttf-dmcasansserif && cd ttf-dmcasansserif && \
      curl -L -O 'https://typedesign.replit.app/DMCAsansserif9.0-20252.zip' && \
      unzip 'DMCAsansserif9.0-20252.zip' && \
      ls | grep .ttf | xargs -I% -n1 install -Dm644 % /usr/share/fonts/TTF/% && \
      cd - && rm -rf ttf-dmcasansserif


WORKDIR /work
ENV PATH="/usr/bin/vendor_perl:${PATH}"
ENTRYPOINT ["make"]
CMD ["all"]
