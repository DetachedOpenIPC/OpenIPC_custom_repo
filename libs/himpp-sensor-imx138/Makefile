#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=himpp-sensor-imx138
PKG_VERSION:=0.1
PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenIPC/himpp-sensors.git
PKG_SOURCE_DATE:=2017-08-02
PKG_SOURCE_VERSION:=6b2ef53cc3ca1d9879215a2a28a6eee51c64ed10
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz

PKG_MAINTAINER:=Sergey Sharshunov <s.sharshunov@gmail.com>

PKG_BUILD_PARALLEL:=1
# PKG_INSTALL:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

HIMPP_HI35XX_MAKE_OPTS = ARCH=arm
HIMPP_HI35XX_MAKE_OPTS += HIARCH=hi3518
HIMPP_HI35XX_MAKE_OPTS += LIBC=uclibc
HIMPP_HI35XX_MAKE_OPTS += CROSS=$(TARGET_CROSS)
HIMPP_HI35XX_MAKE_OPTS += CROSS_COMPILE=$(TARGET_CROSS)
HIMPP_HI35XX_MAKE_OPTS += LINUX_ROOT=$(LINUX_DIR)
HIMPP_HI35XX_MAKE_OPTS += SDK_PATH=$(PKG_BUILD_DIR)
HIMPP_HI35XX_MAKE_OPTS += SENSOR_TYPE=$(SENSOR_TYPE)

SO_NAME = libsns_imx138.so

define Package/$(PKG_NAME)-template
	SECTION:=OpenIPC_custom
	CATEGORY:=OpenIPC
	SUBMENU:=HiSilicon related
	URL:=https://openipc.org
	MAINTAINER:=Sergey Sharshunov <s.sharshunov@gmail.com>
	TITLE:=HiSilicon hi35xx $(PKG_NAME)
	VARIANT:=$(1)
	DEPENDS:=$(2)
endef

ifeq ($(BUILD_VARIANT),v1)

endif

define Build/Compile
	$(MAKE) all -C $(PKG_BUILD_DIR)/mpp2/component/isp2/sensor $(HIMPP_HI35XX_MAKE_OPTS) LDFLAGS="$(TARGET_LDFLAGS)" \
	CFLAGS="$(EXTRA_CFLAGS) $(TARGET_CPPFLAGS) $(EXTRA_CPPFLAGS)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR)/usr/lib
	$(CP) -r $(PKG_BUILD_DIR)/mpp2/component/isp2/lib/*.* $(STAGING_DIR)/usr/lib/
endef

define Package/$(PKG_NAME)-$(BUILD_VARIANT)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mpp2/component/isp2/lib/$(SO_NAME) $(1)/usr/lib/
endef

DEPS_V1:=@(TARGET_hi35xx_16cv100||TARGET_hi35xx_18av100||TARGET_hi35xx_18cv100||TARGET_hi35xx_18ev100)
DEPS_V1+=@(PACKAGE_himpp-dev-hi3516cv100||PACKAGE_himpp-dev-hi3518av100||PACKAGE_himpp-dev-hi3518cv100||PACKAGE_himpp-dev-hi3518ev100)

DEPS_V2:=@(TARGET_hi35xx_16cv200||TARGET_hi35xx_18ev200||TARGET_hi35xx_18ev201)
DEPS_V2+=@(PACKAGE_himpp-dev-hi3516cv200||PACKAGE_himpp-dev-hi3518ev200||PACKAGE_himpp-dev-hi3518ev201)

DEPS_V3:=@(TARGET_hi35xx_16cv300||TARGET_hi35xx_16ev100)
DEPS_V3+=@(PACKAGE_himpp-dev-hi3516cv300||PACKAGE_himpp-dev-hi3516ev100)

Package/$(PKG_NAME)-v1=$(call Package/$(PKG_NAME)-template,v1,$(DEPS_V1))
Package/$(PKG_NAME)-v2=$(call Package/$(PKG_NAME)-template,v2,$(DEPS_V2))
Package/$(PKG_NAME)-v3=$(call Package/$(PKG_NAME)-template,v3,$(DEPS_V3))

$(eval $(call BuildPackage,$(PKG_NAME)-v1))
$(eval $(call BuildPackage,$(PKG_NAME)-v2))
$(eval $(call BuildPackage,$(PKG_NAME)-v3))
