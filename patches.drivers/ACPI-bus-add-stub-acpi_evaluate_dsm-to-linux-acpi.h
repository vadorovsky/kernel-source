From c6c328d91d184d03fb6b1f2a26d95592da50215c Mon Sep 17 00:00:00 2001
From: Kejian Yan <yankejian@huawei.com>
Date: Fri, 3 Jun 2016 10:55:10 +0800
Subject: [PATCH 07/19] ACPI: bus: add stub acpi_evaluate_dsm() to linux/acpi.h
Git-commit: 4ae399241adba66ad72e5973a1004f37ffbe67cd
Patch-mainline: v4.8-rc1
References: bsc#1043231

acpi_evaluate_dsm() will be used to handle the _DSM method in ACPI case.
It will be compiled in non-ACPI case, but the function is in acpi_bus.h
and acpi_bus.h can only be used in ACPI case, so this patch add the stub
function to linux/acpi.h to make compiled successfully in non-ACPI cases.

Cc: Rafael J. Wysocki <rjw@rjwysocki.net>
Signed-off-by: Kejian Yan <yankejian@huawei.com>
Signed-off-by: Yisen Zhuang <Yisen.Zhuang@huawei.com>
Signed-off-by: David S. Miller <davem@davemloft.net>
Signed-off-by: Matwey V. Kornilov <matwey.kornilov@gmail.com>
Acked-by: Takashi Iwai <tiwai@suse.de>

---
 include/linux/acpi.h |    8 ++++++++
 1 file changed, 8 insertions(+)

--- a/include/linux/acpi.h
+++ b/include/linux/acpi.h
@@ -638,6 +638,14 @@ static inline bool acpi_driver_match_dev
 	return false;
 }
 
+static inline union acpi_object *acpi_evaluate_dsm(acpi_handle handle,
+						   const u8 *uuid,
+						   int rev, int func,
+						   union acpi_object *argv4)
+{
+	return NULL;
+}
+
 static inline int acpi_device_uevent_modalias(struct device *dev,
 				struct kobj_uevent_env *env)
 {
