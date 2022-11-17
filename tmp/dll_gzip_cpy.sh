#!/bin/sh

#- Easy dll copy and deflate disassemble script, for debugging zlib compression

DST="/mnt/r/t4"

DLL="cothemedll"

#- Copy expected DLLs for all versions
tail ~/n64/decomp/bt/expected/usa/dlls/${DLL}.dll -c +19 > ${DST}/${DLL}_usa_vani.cmp
tail ~/n64/decomp/bt/expected/jpn/dlls/${DLL}.dll -c +19 > ${DST}/${DLL}_jpn_vani.cmp
tail ~/n64/decomp/bt/expected/eur/dlls/${DLL}.dll -c +19 > ${DST}/${DLL}_eur_vani.cmp
tail ~/n64/decomp/bt/expected/aus/dlls/${DLL}.dll -c +19 > ${DST}/${DLL}_aus_vani.cmp

#- Copy built DLLs for all versions
tail ~/n64/decomp/bt/build/usa/dlls/${DLL}.dll -c +19 > ${DST}/${DLL}_usa_cust.cmp
tail ~/n64/decomp/bt/build/jpn/dlls/${DLL}.dll -c +19 > ${DST}/${DLL}_jpn_cust.cmp
tail ~/n64/decomp/bt/build/eur/dlls/${DLL}.dll -c +19 > ${DST}/${DLL}_eur_cust.cmp
tail ~/n64/decomp/bt/build/aus/dlls/${DLL}.dll -c +19 > ${DST}/${DLL}_aus_cust.cmp

#- Run infgen for all versions

echo "infgen vani usa"
infgen -i -s -r -dd "${DST}/${DLL}_usa_vani.cmp" > "${DST}/ig_usa_vani.txt"
echo "infgen vani jpn"
infgen -i -s -r -dd "${DST}/${DLL}_jpn_vani.cmp" > "${DST}/ig_jpn_vani.txt"
echo "infgen vani eur"
infgen -i -s -r -dd "${DST}/${DLL}_eur_vani.cmp" > "${DST}/ig_eur_vani.txt"
echo "infgen vani aus"
infgen -i -s -r -dd "${DST}/${DLL}_aus_vani.cmp" > "${DST}/ig_aus_vani.txt"

echo "infgen cust usa"
infgen -i -s -r -dd "${DST}/${DLL}_usa_cust.cmp" > "${DST}/ig_usa.txt"
echo "infgen cust jpn"
infgen -i -s -r -dd "${DST}/${DLL}_jpn_cust.cmp" > "${DST}/ig_jpn.txt"
echo "infgen cust eur"
infgen -i -s -r -dd "${DST}/${DLL}_eur_cust.cmp" > "${DST}/ig_eur.txt"
echo "infgen cust aus"
infgen -i -s -r -dd "${DST}/${DLL}_aus_cust.cmp" > "${DST}/ig_aus.txt"


