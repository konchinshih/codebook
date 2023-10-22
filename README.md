# NYCU PersistentSlackers

Codebook for ICPC team NYCU_PersistentSlackers from National Yang Ming Chiao Tung University.

## Members

- [Benson Wang](https://github.com/benson0402)
- [Gino Huang](https://github.com/Penguin-71630)
- [Ian Shih](https://github.com/konchinshih)

## Ranking

### 2022

- 交大程式設計競賽 新生賽 **Rank 2**
- 交大程式設計競賽 年度賽 **Rank 5**
- ICPC Asia Taiwan Online Programming Contest **Rank 61**
- [National Collegiate Programming Contest](https://web.archive.org/web/20221017103207/https://reg.ncpc.ntnu.edu.tw/ncpc2022/NCPC_final/) **Rank 20** (佳作 1)
- [International Collegiate Programming Contest - Asia Taoyuan Site](https://icpc2022.ntub.edu.tw/final-scoreboard/) **Rank 22** (銀牌)
- 中區大專院校程式設計競賽 **Rank 1**
- 中山大學程式研習社 酒醉程式競賽 大一組 **Rank 1**

### 2023

- 交大程式設計競賽 年度賽 **Rank 4**
- ICPC Asia Taiwan Online Programming Contest **Rank 97**
- National Collegiate Programming Contest **Rank 13**
- HP Codewars 大學組 **Rank 1**

### 2024

- 

## Names

每年想好隊名結果都有新的取名 policy ，又要重想 zzz

- NCTU_BurnChickenGrays
- NYCU_AquaQAway (Naming policy: 油)
- NYCU_Ramenholics
- NYCU_Alcoholic
- NYCU_PersistentSlackers (Naming policy: 演算法或資結相關)

## Codebook Compile

0. Install & Start docker (optionally install docker-buildx in archlinux).
1. Build the docker image (only need to run once): `docker build -t archlatex .` 
2. Compile the codebook: `docker run -v ".:/work" --rm -u "$(id -u):$(id -g)" archlatex`
