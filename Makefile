KERNEL=kernel/skernel

run:
	$(MAKE) -C kernel
	qemu-system-i386 -serial stdio -m 128m -kernel $(KERNEL) -enable-kvm -machine q35 -device intel-iommu -vga std

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C libc clean
