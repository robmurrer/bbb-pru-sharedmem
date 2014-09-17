# Device Tree Overlay Makefile
# Rob Murrer - 2014/08/27

OVERLAY_NAME=PRU-SHARED-MEM
SLOT_NUM=9

# Should not need to touch below
OVERLAY_VERSION=00A0
OVERLAY_SOURCE=$(OVERLAY_NAME)-$(OVERLAY_VERSION).dts
OVERLAY_BIN=$(OVERLAY_NAME)-$(OVERLAY_VERSION).dtbo
DESTINATION=/lib/firmware/
CAPE_MGR=/sys/devices/bone_capemgr.$(SLOT_NUM)/slots

.PHONY: all
all: $(OVERLAY_SOURCE) $(OVERLAY_BIN) copy

$(OVERLAY_BIN):
	dtc -O dtb -o $(OVERLAY_BIN) -b 0 -@ $(OVERLAY_SOURCE)

.PHONY: clean
clean: $(OVERLAY_BIN) $(DESTINATION)$(OVERLAY_BIN)
	rm $(OVERLAY_BIN)
	rm $(DESTINATION)$(OVERLAY_BIN)

.PHONY: copy
copy: $(OVERLAY_BIN)
	cp $(OVERLAY_BIN) $(DESTINATION) 

.PHONY: enable
enable: copy 
	echo $(OVERLAY_NAME) > $(CAPE_MGR)

.PHONY: list
list:
	cat $(CAPE_MGR)
