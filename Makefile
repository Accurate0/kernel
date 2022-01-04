TARGET=kernel/skernel

run: $(TARGET)
	qemu-system-i386 -serial stdio -kernel $(TARGET) -enable-kvm -machine q35 -device intel-iommu -vga std

$(TARGET):
	$(MAKE) -C kernel

clean:
	$(MAKE) -C kernel clean
	$(MAKE) -C libc clean
