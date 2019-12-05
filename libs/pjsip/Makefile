#
# Copyright (C) 2010-2011 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=pjsip
# PKG_VERSION:=1.8.5
PKG_VERSION:=2.9
PKG_RELEASE:=2

PKG_SOURCE:=pjproject-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://www.pjsip.org/release/$(PKG_VERSION)/
PKG_MD5SUM:=66757078e7bd7cf316acb0425c2fdd6f
PKG_INSTALL:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(BUILD_VARIANT)/pjproject-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)-template
	SECTION:=OpenIPC_custom
	CATEGORY:=OpenIPC
	SUBMENU:=Library
	URL:=http://www.pjsip.org/
	MAINTAINER:=Sergey Sharshunov <s.sharshunov@gmail.com>
	TITLE:=pjsip-$(1)
	VARIANT:=$(1)
	DEPENDS:=+libuuid +librt +libstdcpp $(2)
endef

# CONFIGURE_PREFIX=/usr/pjsip-$(BUILD_VARIANT)

# ifeq ($(BUILD_VARIANT),oss)
# CONFIGURE_ARGS += \
# 	--enable-g711-codec \
# 	--disable-l16-codec \
# 	--disable-g722-codec \
# 	--disable-g7221-codec \
# 	--disable-gsm-codec \
# 	--disable-ilbc-coder \
# 	--disable-libsamplerate \
# 	--disable-ipp \
# 	--disable-ssl \
# 	--enable-oss \
# 	--enable-sound
# endif

ifeq ($(BUILD_VARIANT),hisi)
CONFIGURE_ARGS += \
    --disable-small-filter \
    --disable-bcg729 \
    --disable-libwebrtc \
    --disable-ffmpeg \
    --disable-v4l2 \
    --disable-openh264 \
    --disable-sdl \
    --disable-gsm-codec \
    --disable-opencore-amr \
    --disable-speex-aec \
    --disable-l16-codec \
    --disable-g722-codec \
    --disable-g7221-codec \
    --disable-ilbc-codec \
    --disable-speex-codec \
    --disable-large-filter \
	--disable-libsamplerate \
	--disable-ipp \
	--disable-ssl \
	--disable-oss \
    --enable-shared \
	--enable-sound \
	--disable-resample \
	--disable-g711-codec \
	--disable-darwin-ssl \
	--disable-sil
endif

# Package/$(PKG_NAME)-oss=$(call Package/$(PKG_NAME)-template,oss,)
Package/$(PKG_NAME)-hisi=$(call Package/$(PKG_NAME)-template,hisi,+libopus)

define Build/Prepare
	$(PKG_UNPACK)
	$(Build/Patch)
endef

define Build/Configure
	$(call Build/Configure/Default)
endef

define Build/Compile
    $(MAKE) all -C $(PKG_BUILD_DIR)/$(MAKE_PATH) LD="$(TARGET_CC)" LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)
	$(CP) $(PKG_INSTALL_DIR)/usr/ $(1)
endef

define Package/$(PKG_NAME)-$(BUILD_VARIANT)/install
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.s* $(1)/usr/lib/
endef

# $(eval $(call BuildPackage,$(PKG_NAME)-oss))
$(eval $(call BuildPackage,$(PKG_NAME)-hisi))
