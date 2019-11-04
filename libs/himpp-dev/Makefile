#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=himpp-dev
PKG_VERSION:=1.0.B.0
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenIPC/himpp-dev.git
PKG_SOURCE_DATE:=2017-08-02
PKG_SOURCE_VERSION:=0ea83eea801cb98392e6dd5f842553cc96a6ac4c
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)

# PKG_SOURCE:=hi3518v100-mpp2-$(PKG_SOURCE_VERSION).tgz
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz

PKG_MAINTAINER:=Sergey Sharshunov <s.sharshunov@gmail.com>

PKG_BUILD_PARALLEL:=1
# PKG_INSTALL:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

HIMPP_VERSIONS:=16cv100
HIMPP_VERSIONS+=16cv200
HIMPP_VERSIONS+=16cv300
HIMPP_VERSIONS+=16ev100
HIMPP_VERSIONS+=18av100
HIMPP_VERSIONS+=18cv100
HIMPP_VERSIONS+=18ev100
HIMPP_VERSIONS+=18ev200
HIMPP_VERSIONS+=18ev201

define Package/$(PKG_NAME)/template
define Package/$(PKG_NAME)-hi35$(1)
	SECTION:=OpenIPC_custom
	CATEGORY:=OpenIPC
	SUBMENU:=HiSilicon related
	URL:=https://openipc.org
	MAINTAINER:=Sergey Sharshunov <s.sharshunov@gmail.com>
	TITLE:=HiSilicon hi35$(1) himpp
	VARIANT:=$(1)
	DEPENDS:=@(TARGET_hi35xx_$(1)) $(2)
endef
endef

define BuildHimppPackage
	$(eval $($(PKG_NAME)/$(1)))
	$(call Package/$(PKG_NAME)/template,$(1),)
endef

ifdef BUILD_VARIANT
$(eval $(call $(PKG_NAME)/$(BUILD_VARIANT)))

ifeq (,$(filter $(BUILD_VARIANT),16cv100 18av100 18cv100 18ev100))
	HIMPP_SDK_VERSION = 1.0.B.0
	HIMPP_SDK_SOURCE = hi3518v100-mpp2-$(HIMPP_SDK_VERSION).tgz
endif
ifeq (,$(filter $(BUILD_VARIANT),16cv200 18ev200 18ev201))
	HIMPP_SDK_VERSION = 1.0.4.1
	HIMPP_SDK_SOURCE = hi3518v200-mpp2-$(HIMPP_SDK_VERSION).tgz
endif
ifeq (,$(filter $(BUILD_VARIANT),16cv300 16ev100))
	HIMPP_SDK_VERSION = 1.0.B.0
	HIMPP_SDK_SOURCE = hi3518v100-mpp2-$(HIMPP_SDK_VERSION).tgz
endif

HIMPP_HI35XX_MAKE_OPTS = ARCH=arm
HIMPP_HI35XX_MAKE_OPTS += HIARCH=hi3518
HIMPP_HI35XX_MAKE_OPTS += LIBC=uclibc
HIMPP_HI35XX_MAKE_OPTS += CROSS=$(TARGET_CROSS)
HIMPP_HI35XX_MAKE_OPTS += CROSS_COMPILE=$(TARGET_CROSS)
HIMPP_HI35XX_MAKE_OPTS += LINUX_ROOT=$(LINUX_DIR)
HIMPP_HI35XX_MAKE_OPTS += SDK_PATH=$(PKG_BUILD_DIR)
HIMPP_HI35XX_MAKE_OPTS += SENSOR_TYPE=$(SENSOR_TYPE)
endif

define Build/Prepare
	$(call Build/Prepare/Default)
	$(TAR) -zxf $(PKG_BUILD_DIR)/$(HIMPP_SDK_SOURCE) \
		--strip-components=1 -C $(PKG_BUILD_DIR)
	find $(PKG_BUILD_DIR) -name .svn | $(XARGS) rm -rf
endef

define Build/Compile
	$(MAKE) all -C $(PKG_BUILD_DIR)/mpp2/extdrv $(HIMPP_HI35XX_MAKE_OPTS) LDFLAGS="$(TARGET_LDFLAGS)" \
	CFLAGS="$(EXTRA_CFLAGS) $(TARGET_CPPFLAGS) $(EXTRA_CPPFLAGS)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR)/usr/include
	$(CP) -r $(PKG_BUILD_DIR)/mpp2/include/* $(STAGING_DIR)/usr/include/
	$(INSTALL_DIR) $(STAGING_DIR)/usr/lib
	$(CP) -r $(PKG_BUILD_DIR)/mpp2/lib/*.* $(STAGING_DIR)/usr/lib/
endef

define Package/$(PKG_NAME)-hi35$(BUILD_VARIANT)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/lib/ko
	$(INSTALL_DIR) $(1)/usr/lib/ko/extdrv
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mpp2/ko/extdrv/*.ko $(1)/usr/lib/ko/extdrv
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mpp2/ko/*.ko $(1)/usr/lib/ko
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mpp2/lib/*.so $(1)/usr/lib/
endef

$(foreach hv,$(HIMPP_VERSIONS), \
	$(eval $(call BuildHimppPackage,$(hv))) \
	$(eval $(call BuildPackage,$(PKG_NAME)-hi35$(hv))) \
)