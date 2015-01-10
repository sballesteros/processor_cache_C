#include <iostream>
#include <array>

typedef unsigned int uint32_t;

struct asm_registers {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
};

void get_cpu_info_by_code(int code, asm_registers *registers) {
    __asm__ volatile (
    "cpuid;"
    :"=a"(registers->eax),"=b"(registers->ebx),"=c"(registers->ecx), "=d"(registers->edx)
    :"a"(code)
    :
    );
}

std::string get_vendor() {
    asm_registers registers;
    memset(&registers, 0, sizeof registers);
    get_cpu_info_by_code(0x0, &registers);
    std::array<char, 13> vendor_name;
    std::array<uint32_t, 3> identity_reg { registers.ebx, registers.ecx, registers.edx};
    std::for_each(identity_reg.begin(), identity_reg.end(), [&vendor_name, identity_reg](uint32_t register_value) {
        auto it = std::find(identity_reg.begin(), identity_reg.end(), register_value);
        if (it != identity_reg.end()) {
            auto index = std::distance(identity_reg.begin(), it);
            auto partitions = sizeof(uint32_t);
            for (uint32_t j = 0; j < partitions; j++) {
                vendor_name[index * partitions + j] = identity_reg[index] >> (j * 8) & 0xFF;
            }
        }
    });
    return std::string(vendor_name.__elems_);
}

uint32_t get_cache_size() {
    asm_registers registers;
    memset(&registers, 0, sizeof registers);
    get_cpu_info_by_code(0x80000006, &registers);
    return (registers.ecx & 0xFF);
}

int main() {
    std::cout << "vendor name= " << get_vendor() << std::endl;
    std::cout << "L2 cache size= " << get_cache_size() << std::endl;
}