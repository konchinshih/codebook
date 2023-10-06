# NYCU PersistentSlackers

每年想好隊名結果都有新的取名 policy ，又要重想 zzz

## Compile
0. Install & Start docker (optionally install docker-buildx in archlinux).
1. Build the docker image (only need to run once): `docker build -t archlatex .` 
2. Compile the codebook: `docker run -v ".:/work" --rm -u "$(id -u):$(id -g)" archlatex`
