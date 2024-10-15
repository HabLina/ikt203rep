# Knuth-Morris-Pratt (KMP)

# Pattern shifting
I computer science, er algoritmen KMP en string-søkende algoritme. Den søker
etter forekomster av et ord "W" i en string "S" ved å ta i bruk observasjonen
ved når et misforhold oppstår, vil ordet selv inneholde tilstrekkelig 
informasjon til å bestemme hvor neste string-søk skal starte. Dermed omgår
en ny undersøkelde av den tidligere matchende tegnet.

## Eksempel forklaring:
Gitt en tekst txt[0 ... N-1] og mønsteret pat[0 ... M-1], skriv en funskjon
search(char pat[], char txt[]) som printer ut alle utfall hvor pat[] i txt[].
Vi antar at N > M.

Input:  txt[] = "AABAACAADAABAABA"
        pat[] = "AABA"
Output: Mønsteret ble funnet ved index 0, Mønsteret ble funnet med index 9 og
        Mønsteret ble funnet ved index 12

![img.png](images/img.png)

## Prefix table
KMP bruker prefix tabell for å søke effektivt etter forekomster av et mønster i
en string. Prefix tabellen inneholder infomasjon om lengden av den lengste
prefikssuffiksen for hver posisjon i mønsteret. 
Det gjør at algoritmen kan hoppe fremover i teksten ved feil samsvar og unngå
unødvendinge sammenligninger.
    - starter med 0, siden det ikke er noen prefikssuffikser i et
      enkelt tegnmønster
    - deretter begynner vi å sjekke for økende lengder som samsvarer mønsteret,
      dersom de samsvarer øker lengden med 1.
    - ved mismatch, går vi tilbake til den sist matchende posisjonen i mønsteret
    - dersom vi når starten av mønsteret (j blir null) uten match, øker vi "i" for neste tegn

Prefix tabell for pat[]:
        pat[] = "AABA"
        Prefix table: [0, 1, 0, 1]