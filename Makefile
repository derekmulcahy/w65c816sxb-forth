SXB_DEVICE=/dev/cu.usbserial-A902WURK

#===============================================================================
# CC65 Tools Assembler Definitions
#-------------------------------------------------------------------------------

AS          = ca65
LD          = cl65
RM          = rm
AS_FLAGS   += --listing $(@:.obj=.lst) -o $@ -DW65C816SXB # -DUSE_FIFO=1
LD_FLAGS    =  -C $(CFG) -vm -m $(MAP)

#===============================================================================
# Rules
#-------------------------------------------------------------------------------

.asm.obj:
	$(AS) $(AS_FLAGS) $<

#===============================================================================
# Targets
#-------------------------------------------------------------------------------

CFG     = ans-forth.cfg
MAP     = ans-forth.map
SREC	= ans-forth.s19
BINS    = forth-0x0200.bin forth-0x0300.bin forth-0x0400.bin forth-0x7EE0.bin
WDCS    =   wdc-0x0200.bin   wdc-0x0300.bin   wdc-0x0400.bin   wdc-0x7EE0.bin
INCS	= ca65.inc w65c816.inc w65c816sxb.inc
OBJS	= w65c816sxb.obj ans-forth.obj
LSTS	= w65c816sxb.lst ans-forth.lst

all: split $(BINS) $(SREC)

clean:
	$(RM) -f $(OBJS) $(BINS) $(SREC)
	$(RM) -f wdc-0x*.bin

debug:
	$(DEBUG)

#===============================================================================
# Dependencies
#-------------------------------------------------------------------------------

$(BINS): $(OBJS) $(INCS) $(WDCS)
	$(LD) $(LD_FLAGS) -o $@ $(OBJS)
	cmp wdc-0x0200.bin forth-0x0200.bin
	cmp wdc-0x0300.bin forth-0x0300.bin
	cmp wdc-0x0400.bin forth-0x0400.bin
	cmp wdc-0x7EE0.bin forth-0x7EE0.bin

prog: $(BINS)
	./sxb.py -d $(SXB_DEVICE) write 0x0200 forth-0x0200.bin
	./sxb.py -d $(SXB_DEVICE) write 0x0300 forth-0x0300.bin
	./sxb.py -d $(SXB_DEVICE) write 0x0400 forth-0x0400.bin
	./sxb.py -d $(SXB_DEVICE) write 0x7EE0 forth-0x7EE0.bin
	./sxb.py -d $(SXB_DEVICE) exec 0x0300

wdc:
	./sxb.py -d $(SXB_DEVICE) wdc ans-forth.bin

split:
	./sxb.py -d $(SXB_DEVICE) split ans-forth.bin

$(SREC): $(BINS)
	srec_cat  -o $(SREC)\
		-data-only\
		-execution_start_address 0x0300\
		-address-length 2 -line-length 46\
		forth-0x0200.bin -binary -offset 0x0200\
		forth-0x0300.bin -binary -offset 0x0300\
		forth-0x0400.bin -binary -offset 0x0400\
		forth-0x7EE0.bin -binary -offset 0x7EE0

w65c816sxb.obj:  w65c816.inc w65c816sxb.inc w65c816sxb.asm
ans-forth.obj: w65c816.inc device.asm ans-forth.asm

.SUFFIXES: .asm .obj
