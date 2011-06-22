From: Michal Marek <mmarek@suse.cz>
Date: Tue, 9 Mar 2010 16:00:20 +0100
Subject: [PATCH] kbuild: Really don't clean bounds.h and asm-offsets.h
Patch-mainline: Submitted for 2.6.37-rc1
References: bnc#585743
Git-commit: ef8ff89b58546055e238c3b521f83b440dfe8ef2

Commit 7d3cc8b tried to keep bounds.h and asm-offsets.h during make
clean by filtering these out of $(clean-files), but they are listed in
$(targets) and $(always) and thus removed automatically. Introduce a new
$(no-clean-files) variable to really skip such files in Makefile.clean.

Signed-off-by: Michal Marek <mmarek@suse.cz>
---
 Documentation/kbuild/makefiles.txt |    7 +++++++
 Kbuild                             |    4 ++--
 scripts/Makefile.clean             |    2 ++
 3 files changed, 11 insertions(+), 2 deletions(-)

diff --git a/Documentation/kbuild/makefiles.txt b/Documentation/kbuild/makefiles.txt
index 0135155..fcd1a98 100644
--- a/Documentation/kbuild/makefiles.txt
+++ b/Documentation/kbuild/makefiles.txt
@@ -779,6 +779,13 @@ This will delete the directory debian, including all subdirectories.
 Kbuild will assume the directories to be in the same relative path as the
 Makefile if no absolute path is specified (path does not start with '/').
 
+To exclude certain files from make clean, use the $(no-clean-files) variable.
+This is only a special case used in the top level Kbuild file:
+
+	Example:
+		#Kbuild
+		no-clean-files := $(bounds-file) $(offsets-file)
+
 Usually kbuild descends down in subdirectories due to "obj-* := dir/",
 but in the architecture makefiles where the kbuild infrastructure
 is not sufficient this sometimes needs to be explicit.
diff --git a/Kbuild b/Kbuild
index e3737ad..18a8bfb 100644
--- a/Kbuild
+++ b/Kbuild
@@ -94,5 +94,5 @@ PHONY += missing-syscalls
 missing-syscalls: scripts/checksyscalls.sh FORCE
 	$(call cmd,syscalls)
 
-# Delete all targets during make clean
-clean-files := $(addprefix $(objtree)/,$(filter-out $(bounds-file) $(offsets-file),$(targets)))
+# Keep these two files during make clean
+no-clean-files := $(bounds-file) $(offsets-file)
diff --git a/scripts/Makefile.clean b/scripts/Makefile.clean
index 6f89fbb..686cb0d 100644
--- a/scripts/Makefile.clean
+++ b/scripts/Makefile.clean
@@ -45,6 +45,8 @@ __clean-files	:= $(extra-y) $(always)                  \
 		   $(host-progs)                         \
 		   $(hostprogs-y) $(hostprogs-m) $(hostprogs-)
 
+__clean-files   := $(filter-out $(no-clean-files), $(__clean-files))
+
 # as clean-files is given relative to the current directory, this adds
 # a $(obj) prefix, except for absolute paths
 
-- 
1.6.6.1

