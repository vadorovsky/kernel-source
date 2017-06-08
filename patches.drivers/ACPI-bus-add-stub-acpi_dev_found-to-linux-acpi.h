From 55a815d3eb91f9524128ceb9c8acd99fe5e71bdc Mon Sep 17 00:00:00 2001
From: Kejian Yan <yankejian@huawei.com>
Date: Fri, 3 Jun 2016 10:55:09 +0800
Subject: [PATCH 08/19] ACPI: bus: add stub acpi_dev_found() to linux/acpi.h
Git-commit: 6eb17e0df74c036eba7548915b37f009403fe09e
Patch-mainline: v4.8-rc1
References: bsc#1043231

acpi_dev_found() will be used to detect if a given ACPI device is in the
system. It will be compiled in non-ACPI case, but the function is in
acpi_bus.h and acpi_bus.h can only be used in ACPI case, so this patch add
the stub function to linux/acpi.h to make compiled successfully in
non-ACPI cases.

Cc: Rafael J. Wysocki <rjw@rjwysocki.net>
Signed-off-by: Kejian Yan <yankejian@huawei.com>
Signed-off-by: Yisen Zhuang <Yisen.Zhuang@huawei.com>
Signed-off-by: David S. Miller <davem@davemloft.net>
Signed-off-by: Matwey V. Kornilov <matwey.kornilov@gmail.com>
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 include/linux/acpi.h |    5 +++++
 1 file changed, 5 insertions(+)

--- a/include/linux/acpi.h
+++ b/include/linux/acpi.h
@@ -528,6 +528,11 @@ int acpi_arch_timer_mem_init(struct arch
 
 struct fwnode_handle;
 
+static inline bool acpi_dev_found(const char *hid)
+{
+	return false;
+}
+
 static inline bool is_acpi_node(struct fwnode_handle *fwnode)
 {
 	return false;
