#!/bin/sh

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

GDRCOIND=${GDRCOIND:-$SRCDIR/gdrcoind}
GDRCOINCLI=${GDRCOINCLI:-$SRCDIR/gdrcoin-cli}
GDRCOINTX=${GDRCOINTX:-$SRCDIR/gdrcoin-tx}
GDRCOINQT=${GDRCOINQT:-$SRCDIR/qt/gdrcoin-qt}

[ ! -x $GDRCOIND ] && echo "$GDRCOIND not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
MARKVER=($($GDRCOINCLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for gdrcoind if --version-string is not set,
# but has different outcomes for gdrcoin-qt and gdrcoin-cli.
echo "[COPYRIGHT]" > footer.h2m
$GDRCOIND --version | sed -n '1!p' >> footer.h2m

for cmd in $GDRCOIND $GDRCOINCLI $GDRCOINTX $GDRCOINQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${MARKVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${MARKVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
