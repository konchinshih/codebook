# NYCU LLLemonade Jam

Codebook for ICPC team NYCU_LLLemonade_Jam from National Yang Ming Chiao Tung University.

## Members

- [(former) Benson (Jui-Yu Wang)](https://github.com/benson0402)
- [Gino (Zhi-Hao Huang)](https://github.com/Penguin-71630)
- [Ian (Yi-Ting Shih)](https://github.com/konchinshih)
- [koukanni (Kuan-Wei Huang)](https://github.com/koukanni)

## Ranking

### 2022

- 交大程式設計競賽 新生賽 **Rank 2**
- 交大程式設計競賽 年度賽 **Rank 5**
- ICPC Asia Taiwan Online Programming Contest **Rank 61**
- [National Collegiate Programming Contest](https://web.archive.org/web/20221017103207/https://reg.ncpc.ntnu.edu.tw/ncpc2022/NCPC_final/) **Rank 20** (佳作 1)
- [ICPC Asia Taoyuan Regional](https://icpc2022.ntub.edu.tw/final-scoreboard/) **Rank 22** (silver medal)
- 中區大專院校程式設計競賽 **Rank 1**
- 中山大學程式研習社 酒醉程式競賽 大一組 **Rank 1**

### 2023

- 交大程式設計競賽 年度賽 **Rank 4**
- ICPC Asia Taiwan Online Programming Contest **Rank 97**
- National Collegiate Programming Contest **Rank 13**
- HP Codewars 大學組 **Rank 1**

### 2025

- 交大程式設計競賽 年度賽 **Rank 4**
- ICPC Asia Taiwan Online Programming Contest **Rank 23**
- [National Collegiate Programming Contest](https://web.archive.org/web/20251028135558/https://ncpc.nsysu.edu.tw/static/file/62/1062/img/ScoreboardNCPC2025_FINAL-DOMjudge.pdf) **Rank 11** 
- [ICPC Asia Bangkok Regional](https://icpc.global/regionals/finder/Bangkok-2026/standings) **Rank 16**
- [ICPC Asia Taichung Regional](https://taichung2025.icpc.tw/) **Rank 22** (silver medal)

## Names

每年想好隊名結果都有新的取名 policy ，又要重想 zzz

- NCTU_BurnChickenGrays
- NYCU_AquaQAway (Naming policy: 油)
- NYCU_Ramenholics
- NYCU_Alcoholic
- NYCU_PersistentSlackers (Naming policy: 演算法或資結相關)
- NYCU_LLLemonade_Jam (Naming policy: 樂團)
- NYCU_This_Page_Was_Intentionally_Left_Blank (暫定)


## Compile (Typst)

For Docker:

0. Install & Start docker (optionally install docker-buildx in archlinux).
1. Run `make typst`.

For VSCode:

0. Install the extension `Tinymist`.
1. Run `make typst` in VSCode terminal.


### Code Block Palette

Edit `themes/codeblock-palette.json`, then regenerate the TextMate theme with:

```sh
python3 make-palette.py
```

Foreground colors can be written as `hsl(H, S%, L%)`; the script converts them
to the hexadecimal format required by TextMate. Hex colors such as `#FF6188`
are also accepted.

To test the Dockerfile locally on an arm64 machine, build the project's amd64
image first, then override the image name when running the Docker recipe:

```sh
docker buildx build --platform linux/amd64 --load --tag codebook:local .
DOCKER_IMAGE=codebook:local make docker typst
```





## Compile (LaTeX)

0. Install & Start docker (optionally install docker-buildx in archlinux).
1. Run `make docker`.




## Credits

This codebook incorporates adapted code and materials from:

- KACTL — KTH Algorithm Competition Template Library  
  https://github.com/kth-competitive-programming/kactl
- ckiseki  
  https://github.com/OmeletWithoutEgg/ckiseki

We sincerely thank the original authors and contributors for their excellent work.



