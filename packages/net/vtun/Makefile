#
# Copyright (C) 2006-2009 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=vtun
PKG_VERSION:=3.0.4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=@SF/vtun
PKG_MD5SUM:=f952c5895ae8f40235aaad9a8f41a4bd

PKG_MAINTAINER:=Sergey Sharshunov <s.sharshunov@gmail.com>

include $(INCLUDE_DIR)/package.mk

define Package/vtun
  SECTION:=OpenIPC_custom
  CATEGORY:=OpenIPC
  SUBMENU:=VPN
  DEPENDS:=@TARGET_hi35xx +kmod-tun +liblzo +zlib +libopenssl
  TITLE:=VPN tunneling daemon
  URL:=http://vtun.sourceforge.net
  MENU:=1
endef

define Package/vtun/conffiles
/etc/vtund.conf
endef

define Build/Compile
	$(call Build/Compile/Default,vtund)
endef

define Package/vtun/install
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_CONF) $(PKG_BUILD_DIR)/vtund.conf $(1)/etc/
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/vtund $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,vtun))