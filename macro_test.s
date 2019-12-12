*----------------------------------------------------------------------
* Programmer:
* Class Account:
* Assignment or Title:
* Filename:
* Date completed:
*----------------------------------------------------------------------
* Problem statement:
* Input:
* Output:
* Error conditions tested:
* Included files:
* Method and/or pseudocode:
* References:
*----------------------------------------------------------------------
*
        ORG     $0
        DC.L    $3000           * Stack pointer value after a reset
        DC.L    start           * Program counter value after a reset
        ORG     $3000           * Start at location 3000 Hex
*
*----------------------------------------------------------------------
*
#minclude /home/cs/faculty/riggins/bsvc/macros/iomacs.s
#minclude /home/cs/faculty/riggins/bsvc/macros/evtmacs.s

stripp	macro
	movem.l	A1-A4,-(SP)
	lea      \1,A1 * A1 points to source byte to move
   	movea.l  A1,A4 * copy start to get length of new string
	movea.l	A1,A2 * A2 points to destination byte.
	movea.l	A1,A3 * A3 indicates end of string
	adda.l	\2,A3
	cmpa.l	A1,A3 * if string is 0 length or less
	BLE	nadaMCR\@
	cmpi.b	#'-',(A1)
	BNE	loopMCR\@
	adda.l	#1,A1 * found a minus sign, skip over it
	adda.l	#1,A2
loopMCR\@:
	cmpa	A1,A3 * quit condition
	BEQ	doneMCR\@
	cmpi.b	#'0',(A1)
	BNE	nextMCR\@	* move A1 down until we hit a nonzero digit
	adda.l	#1,A1
	BRA	loopMCR\@
nextMCR\@:
	cmpa	A1,A3 * quit condition
	BEQ	doneMCR\@
	move.b	(A1)+,(A2)+   * move digits following leading zeros
	BRA	nextMCR\@
doneMCR\@:
   	suba.l  A4,A2
   	move.l  A2,D0
	tst.l	D0	*if the number was all zeros, return one zero.
	BGT	outMCR\@
	move.b	#$30,(A4)
	move.l	#1,D0
	BRA	outMCR\@
nadaMCR\@: move.l	#0,D0
outMCR\@:  movem.l	(SP)+,A1-A4
	endm


start:

	stripp	num,#9

        break                   * Terminate execution
*
*----------------------------------------------------------------------
*       Storage declarations

num:	dc.b	'000000025'

        end


