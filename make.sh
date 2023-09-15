COMPILER="xelatex"
TEAMNAME="NYCU_PersistentSlackers"
SRC="${TEAMNAME}.tex"
OUTPUT="${TEAMNAME}.pdf"

${COMPILER} ${SRC}
${COMPILER} ${SRC}
ls | grep ${TEAMNAME} | grep -xv ${SRC} | grep -xv ${OUTPUT} | xargs rm

