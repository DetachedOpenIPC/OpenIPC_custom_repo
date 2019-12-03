#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=histreamer
PKG_VERSION:=0.1
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/OpenIPC/histreamer.git
PKG_SOURCE_DATE:=2017-08-02
PKG_SOURCE_VERSION:=ab13dc88a0c941456043670b7793f67f1ef2d8c2
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz

PKG_MAINTAINER:=Sergey Sharshunov <s.sharshunov@gmail.com>

PKG_BUILD_PARALLEL:=1
PKG_INSTALL:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

CMAKE_PREFIX_PATH:=$(STAGING_DIR)

STREAMER_VERSIONS:=audio
STREAMER_VERSIONS+=video

define Package/$(PKG_NAME)/template
define Package/$(PKG_NAME)-$(1)
	SECTION:=OpenIPC_custom
	CATEGORY:=OpenIPC
	SUBMENU:=Multimedia
	URL:=https://openipc.org
	MAINTAINER:=Sergey Sharshunov <s.sharshunov@gmail.com>
	DEPENDS:=@TARGET_hi35xx
	TITLE:=HiSilicon $(1) rtp streamer
	VARIANT:=$(1)
	DEPENDS:=+pjsip-hisi $(2)
endef
endef

define BuildHiStreamerPackage
	$(eval $($(PKG_NAME)/$(1)))
	$(call Package/$(PKG_NAME)/template,$(1),+libopus)
endef

ifdef BUILD_VARIANT
CMAKE_OPTIONS+=-DCMAKE_CONFIGURATION_TYPES=$(BUILD_VARIANT)
$(eval $(call $(PKG_NAME)/$(BUILD_VARIANT)))
endif

define Build/Compile
	$(MAKE) all -C $(PKG_BUILD_DIR)/$(MAKE_PATH) LD="$(TARGET_CC)" LDFLAGS="$(TARGET_LDFLAGS)" \
	CFLAGS="$(EXTRA_CFLAGS) $(TARGET_CPPFLAGS) $(EXTRA_CPPFLAGS)"
endef

define Package/$(PKG_NAME)-$(BUILD_VARIANT)/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT) $(1)/usr/bin/
endef

$(foreach st,$(STREAMER_VERSIONS), \
	$(eval $(call BuildHiStreamerPackage,$(st))) \
	$(eval $(call BuildPackage,$(PKG_NAME)-$(st))) \
)