# To build modules outside of the kernel tree, we run "make"
# in the kernel source tree; the Makefile these then includes this
# Makefile once again.
# This conditional selects whether we are being included from the
# kernel Makefile or not.

# called from kernel build system: just declare what our modules are
obj-y += ast.o
ast-objs := ast_drv.o ast_main.o ast_mode.o ast_ttm.o ast_post.o ast_dp501.o ast_dp.o ast_hdmitx.o


