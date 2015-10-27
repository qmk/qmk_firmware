;/**************************************************************************//**
; * @file     core_ca_mmu.h
; * @brief    MMU Startup File for
; *           VE_A9_MP Device Series
; * @version  V1.01
; * @date     25 March 2013
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef _MMU_FUNC_H
#define _MMU_FUNC_H

#define SECTION_DESCRIPTOR      (0x2)
#define SECTION_MASK            (0xFFFFFFFC)

#define SECTION_TEXCB_MASK      (0xFFFF8FF3)
#define SECTION_B_SHIFT         (2)
#define SECTION_C_SHIFT         (3)
#define SECTION_TEX0_SHIFT      (12)
#define SECTION_TEX1_SHIFT      (13)
#define SECTION_TEX2_SHIFT      (14)

#define SECTION_XN_MASK         (0xFFFFFFEF)
#define SECTION_XN_SHIFT        (4)

#define SECTION_DOMAIN_MASK     (0xFFFFFE1F)
#define SECTION_DOMAIN_SHIFT    (5)

#define SECTION_P_MASK          (0xFFFFFDFF)
#define SECTION_P_SHIFT         (9)

#define SECTION_AP_MASK         (0xFFFF73FF)
#define SECTION_AP_SHIFT        (10)
#define SECTION_AP2_SHIFT       (15)

#define SECTION_S_MASK          (0xFFFEFFFF)
#define SECTION_S_SHIFT         (16)

#define SECTION_NG_MASK         (0xFFFDFFFF)
#define SECTION_NG_SHIFT        (17)

#define SECTION_NS_MASK         (0xFFF7FFFF)
#define SECTION_NS_SHIFT        (19)


#define PAGE_L1_DESCRIPTOR      (0x1)
#define PAGE_L1_MASK            (0xFFFFFFFC)

#define PAGE_L2_4K_DESC         (0x2)
#define PAGE_L2_4K_MASK         (0xFFFFFFFD)

#define PAGE_L2_64K_DESC        (0x1)
#define PAGE_L2_64K_MASK        (0xFFFFFFFC)

#define PAGE_4K_TEXCB_MASK      (0xFFFFFE33)
#define PAGE_4K_B_SHIFT         (2)
#define PAGE_4K_C_SHIFT         (3)
#define PAGE_4K_TEX0_SHIFT      (6)
#define PAGE_4K_TEX1_SHIFT      (7)
#define PAGE_4K_TEX2_SHIFT      (8)

#define PAGE_64K_TEXCB_MASK     (0xFFFF8FF3)
#define PAGE_64K_B_SHIFT        (2)
#define PAGE_64K_C_SHIFT        (3)
#define PAGE_64K_TEX0_SHIFT     (12)
#define PAGE_64K_TEX1_SHIFT     (13)
#define PAGE_64K_TEX2_SHIFT     (14)

#define PAGE_TEXCB_MASK         (0xFFFF8FF3)
#define PAGE_B_SHIFT            (2)
#define PAGE_C_SHIFT            (3)
#define PAGE_TEX_SHIFT          (12)

#define PAGE_XN_4K_MASK         (0xFFFFFFFE)
#define PAGE_XN_4K_SHIFT        (0)
#define PAGE_XN_64K_MASK        (0xFFFF7FFF)
#define PAGE_XN_64K_SHIFT       (15)


#define PAGE_DOMAIN_MASK        (0xFFFFFE1F)
#define PAGE_DOMAIN_SHIFT       (5)

#define PAGE_P_MASK             (0xFFFFFDFF)
#define PAGE_P_SHIFT            (9)

#define PAGE_AP_MASK            (0xFFFFFDCF)
#define PAGE_AP_SHIFT           (4)
#define PAGE_AP2_SHIFT          (9)

#define PAGE_S_MASK             (0xFFFFFBFF)
#define PAGE_S_SHIFT            (10)

#define PAGE_NG_MASK            (0xFFFFF7FF)
#define PAGE_NG_SHIFT           (11)

#define PAGE_NS_MASK            (0xFFFFFFF7)
#define PAGE_NS_SHIFT           (3)

#define OFFSET_1M               (0x00100000)
#define OFFSET_64K              (0x00010000)
#define OFFSET_4K               (0x00001000)

#define DESCRIPTOR_FAULT        (0x00000000)

/* ###########################  MMU Function Access  ########################### */
/** \ingroup  MMU_FunctionInterface
    \defgroup MMU_Functions MMU Functions Interface
  @{
 */

/* Attributes enumerations */

/* Region size attributes */
typedef enum
{
   SECTION,
   PAGE_4k,
   PAGE_64k,
} mmu_region_size_Type;

/* Region type attributes */
typedef enum
{
   NORMAL,
   DEVICE,
   SHARED_DEVICE,
   NON_SHARED_DEVICE,
   STRONGLY_ORDERED
} mmu_memory_Type;

/* Region cacheability attributes */
typedef enum
{
   NON_CACHEABLE,
   WB_WA,
   WT,
   WB_NO_WA,
} mmu_cacheability_Type;

/* Region parity check attributes */
typedef enum
{
   ECC_DISABLED,
   ECC_ENABLED,
} mmu_ecc_check_Type;

/* Region execution attributes */
typedef enum
{
   EXECUTE,
   NON_EXECUTE,
} mmu_execute_Type;

/* Region global attributes */
typedef enum
{
   GLOBAL,
   NON_GLOBAL,
} mmu_global_Type;

/* Region shareability attributes */
typedef enum
{
   NON_SHARED,
   SHARED,
} mmu_shared_Type;

/* Region security attributes */
typedef enum
{
   SECURE,
   NON_SECURE,
} mmu_secure_Type;

/* Region access attributes */
typedef enum
{
   NO_ACCESS,
   RW,
   READ,
} mmu_access_Type;

/* Memory Region definition */
typedef struct RegionStruct {
    mmu_region_size_Type rg_t;
    mmu_memory_Type mem_t;
    uint8_t domain;
    mmu_cacheability_Type inner_norm_t;
    mmu_cacheability_Type outer_norm_t;
    mmu_ecc_check_Type e_t;
    mmu_execute_Type xn_t;
    mmu_global_Type g_t;
    mmu_secure_Type sec_t;
    mmu_access_Type priv_t;
    mmu_access_Type user_t;
    mmu_shared_Type sh_t;

} mmu_region_attributes_Type;

/** \brief  Set section execution-never attribute

    The function sets section execution-never attribute

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]                xn  Section execution-never attribute : EXECUTE , NON_EXECUTE.

    \return          0  
 */
__STATIC_INLINE int __xn_section(uint32_t *descriptor_l1, mmu_execute_Type xn)
{
    *descriptor_l1 &= SECTION_XN_MASK;
    *descriptor_l1 |= ((xn & 0x1) << SECTION_XN_SHIFT);
    return 0;
}

/** \brief  Set section domain

    The function sets section domain

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]            domain  Section domain

    \return          0  
 */
__STATIC_INLINE int __domain_section(uint32_t *descriptor_l1, uint8_t domain)
{
    *descriptor_l1 &= SECTION_DOMAIN_MASK;
    *descriptor_l1 |= ((domain & 0xF) << SECTION_DOMAIN_SHIFT);
    return 0;
}

/** \brief  Set section parity check

    The function sets section parity check

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]              p_bit Parity check: ECC_DISABLED, ECC_ENABLED

    \return          0  
 */
__STATIC_INLINE int __p_section(uint32_t *descriptor_l1, mmu_ecc_check_Type p_bit)
{
    *descriptor_l1 &= SECTION_P_MASK;
    *descriptor_l1 |= ((p_bit & 0x1) << SECTION_P_SHIFT);
    return 0;
}

/** \brief  Set section access privileges

    The function sets section access privileges

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]              user  User Level Access: NO_ACCESS, RW, READ
    \param [in]              priv  Privilege Level Access: NO_ACCESS, RW, READ
    \param [in]               afe  Access flag enable

    \return          0  
 */
__STATIC_INLINE int __ap_section(uint32_t *descriptor_l1, mmu_access_Type user, mmu_access_Type priv,  uint32_t afe)
{
    uint32_t ap = 0;

    if (afe == 0) { //full access
        if ((priv == NO_ACCESS) && (user == NO_ACCESS)) { ap = 0x0; }
        else if ((priv == RW) && (user == NO_ACCESS))   { ap = 0x1; }
        else if ((priv == RW) && (user == READ))        { ap = 0x2; }
        else if ((priv == RW) && (user == RW))          { ap = 0x3; }
        else if ((priv == READ) && (user == NO_ACCESS)) { ap = 0x5; }
        else if ((priv == READ) && (user == READ))      { ap = 0x6; }
    }

    else { //Simplified access
        if ((priv == RW) && (user == NO_ACCESS))        { ap = 0x1; }
        else if ((priv == RW) && (user == RW))          { ap = 0x3; }
        else if ((priv == READ) && (user == NO_ACCESS)) { ap = 0x5; }
        else if ((priv == READ) && (user == READ))      { ap = 0x7; }
    }

    *descriptor_l1 &= SECTION_AP_MASK;
    *descriptor_l1 |= (ap & 0x3) << SECTION_AP_SHIFT;
    *descriptor_l1 |= ((ap & 0x4)>>2) << SECTION_AP2_SHIFT;

    return 0;
}

/** \brief  Set section shareability

    The function sets section shareability

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]             s_bit  Section shareability: NON_SHARED, SHARED

    \return          0  
 */
__STATIC_INLINE int __shared_section(uint32_t *descriptor_l1, mmu_shared_Type s_bit)
{
    *descriptor_l1 &= SECTION_S_MASK;
    *descriptor_l1 |= ((s_bit & 0x1) << SECTION_S_SHIFT);
    return 0;
}

/** \brief  Set section Global attribute

    The function sets section Global attribute

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]             g_bit  Section attribute: GLOBAL, NON_GLOBAL

    \return          0  
 */
__STATIC_INLINE int __global_section(uint32_t *descriptor_l1, mmu_global_Type g_bit)
{
    *descriptor_l1 &= SECTION_NG_MASK;
    *descriptor_l1 |= ((g_bit & 0x1) << SECTION_NG_SHIFT);
    return 0;
}

/** \brief  Set section Security attribute

    The function sets section Global attribute

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]             s_bit  Section Security attribute: SECURE, NON_SECURE

    \return          0  
 */
__STATIC_INLINE int __secure_section(uint32_t *descriptor_l1, mmu_secure_Type s_bit)
{
    *descriptor_l1 &= SECTION_NS_MASK;
    *descriptor_l1 |= ((s_bit & 0x1) << SECTION_NS_SHIFT);
    return 0;
}

/* Page 4k or 64k */
/** \brief  Set 4k/64k page execution-never attribute

    The function sets 4k/64k page execution-never attribute

    \param [out]    descriptor_l2  L2 descriptor.
    \param [in]                xn  Page execution-never attribute : EXECUTE , NON_EXECUTE.
    \param [in]              page  Page size: PAGE_4k, PAGE_64k,
   
    \return          0  
 */
__STATIC_INLINE int __xn_page(uint32_t *descriptor_l2, mmu_execute_Type xn, mmu_region_size_Type page)
{
    if (page == PAGE_4k)
    {
        *descriptor_l2 &= PAGE_XN_4K_MASK;
        *descriptor_l2 |= ((xn & 0x1) << PAGE_XN_4K_SHIFT);
    }
    else
    {
        *descriptor_l2 &= PAGE_XN_64K_MASK;
        *descriptor_l2 |= ((xn & 0x1) << PAGE_XN_64K_SHIFT);
    }
    return 0;
}

/** \brief  Set 4k/64k page domain

    The function sets 4k/64k page domain

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]            domain  Page domain

    \return          0  
 */
__STATIC_INLINE int __domain_page(uint32_t *descriptor_l1, uint8_t domain)
{
    *descriptor_l1 &= PAGE_DOMAIN_MASK;
    *descriptor_l1 |= ((domain & 0xf) << PAGE_DOMAIN_SHIFT);
    return 0;
}

/** \brief  Set 4k/64k page parity check

    The function sets 4k/64k page parity check

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]              p_bit Parity check: ECC_DISABLED, ECC_ENABLED

    \return          0  
 */
__STATIC_INLINE int __p_page(uint32_t *descriptor_l1, mmu_ecc_check_Type p_bit)
{
    *descriptor_l1 &= SECTION_P_MASK;
    *descriptor_l1 |= ((p_bit & 0x1) << SECTION_P_SHIFT);
    return 0;
}

/** \brief  Set 4k/64k page access privileges

    The function sets 4k/64k page access privileges

    \param [out]    descriptor_l2  L2 descriptor.
    \param [in]              user  User Level Access: NO_ACCESS, RW, READ
    \param [in]              priv  Privilege Level Access: NO_ACCESS, RW, READ
    \param [in]               afe  Access flag enable

    \return          0  
 */
__STATIC_INLINE int __ap_page(uint32_t *descriptor_l2, mmu_access_Type user, mmu_access_Type priv,  uint32_t afe)
{
    uint32_t ap = 0;

    if (afe == 0) { //full access
        if ((priv == NO_ACCESS) && (user == NO_ACCESS)) { ap = 0x0; }
        else if ((priv == RW) && (user == NO_ACCESS))   { ap = 0x1; }
        else if ((priv == RW) && (user == READ))        { ap = 0x2; }
        else if ((priv == RW) && (user == RW))          { ap = 0x3; }
        else if ((priv == READ) && (user == NO_ACCESS)) { ap = 0x5; }
        else if ((priv == READ) && (user == READ))      { ap = 0x6; }
    }

    else { //Simplified access
        if ((priv == RW) && (user == NO_ACCESS))        { ap = 0x1; }
        else if ((priv == RW) && (user == RW))          { ap = 0x3; }
        else if ((priv == READ) && (user == NO_ACCESS)) { ap = 0x5; }
        else if ((priv == READ) && (user == READ))      { ap = 0x7; }
    }

    *descriptor_l2 &= PAGE_AP_MASK;
    *descriptor_l2 |= (ap & 0x3) << PAGE_AP_SHIFT;
    *descriptor_l2 |= ((ap & 0x4)>>2) << PAGE_AP2_SHIFT;

    return 0;
}

/** \brief  Set 4k/64k page shareability

    The function sets 4k/64k page shareability

    \param [out]    descriptor_l2  L2 descriptor.
    \param [in]             s_bit  4k/64k page shareability: NON_SHARED, SHARED

    \return          0  
 */
__STATIC_INLINE int __shared_page(uint32_t *descriptor_l2, mmu_shared_Type s_bit)
{
    *descriptor_l2 &= PAGE_S_MASK;
    *descriptor_l2 |= ((s_bit & 0x1) << PAGE_S_SHIFT);
    return 0;
}

/** \brief  Set 4k/64k page Global attribute

    The function sets 4k/64k page Global attribute

    \param [out]    descriptor_l2  L2 descriptor.
    \param [in]             g_bit  4k/64k page attribute: GLOBAL, NON_GLOBAL

    \return          0  
 */
__STATIC_INLINE int __global_page(uint32_t *descriptor_l2, mmu_global_Type g_bit)
{
    *descriptor_l2 &= PAGE_NG_MASK;
    *descriptor_l2 |= ((g_bit & 0x1) << PAGE_NG_SHIFT);
    return 0;
}

/** \brief  Set 4k/64k page Security attribute

    The function sets 4k/64k page Global attribute

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]             s_bit  4k/64k page Security attribute: SECURE, NON_SECURE

    \return          0  
 */
__STATIC_INLINE int __secure_page(uint32_t *descriptor_l1, mmu_secure_Type s_bit)
{
    *descriptor_l1 &= PAGE_NS_MASK;
    *descriptor_l1 |= ((s_bit & 0x1) << PAGE_NS_SHIFT);
    return 0;
}


/** \brief  Set Section memory attributes

    The function sets section memory attributes

    \param [out]    descriptor_l1  L1 descriptor.
    \param [in]               mem  Section memory type: NORMAL, DEVICE, SHARED_DEVICE, NON_SHARED_DEVICE, STRONGLY_ORDERED
    \param [in]             outer  Outer cacheability: NON_CACHEABLE, WB_WA, WT, WB_NO_WA,
    \param [in]             inner  Inner cacheability: NON_CACHEABLE, WB_WA, WT, WB_NO_WA,

    \return          0  
 */
__STATIC_INLINE int __memory_section(uint32_t *descriptor_l1, mmu_memory_Type mem, mmu_cacheability_Type outer, mmu_cacheability_Type inner)
{
    *descriptor_l1 &= SECTION_TEXCB_MASK;

    if (STRONGLY_ORDERED == mem)
    {
        return 0;
    }
    else if (SHARED_DEVICE == mem)
    {
        *descriptor_l1 |= (1 << SECTION_B_SHIFT);
    }
    else if (NON_SHARED_DEVICE == mem)
    {
        *descriptor_l1 |= (1 << SECTION_TEX1_SHIFT);
    }
    else if (NORMAL == mem)
    {
           *descriptor_l1 |= 1 << SECTION_TEX2_SHIFT;
           switch(inner)
           {
            case NON_CACHEABLE:
            break;
            case WB_WA:
                *descriptor_l1 |= (1 << SECTION_B_SHIFT);
                break;
            case WT:
                *descriptor_l1 |= 1 << SECTION_C_SHIFT;
                break;
            case WB_NO_WA:
                *descriptor_l1 |= (1 << SECTION_B_SHIFT) | (1 << SECTION_C_SHIFT);
                break;
        }
        switch(outer)
        {
            case NON_CACHEABLE:
             break;
            case WB_WA:
                *descriptor_l1 |= (1 << SECTION_TEX0_SHIFT);
                break;
            case WT:
                *descriptor_l1 |= 1 << SECTION_TEX1_SHIFT;
                break;
            case WB_NO_WA:
                *descriptor_l1 |= (1 << SECTION_TEX0_SHIFT) | (1 << SECTION_TEX0_SHIFT);
                break;
        }
    }

    return 0;
}

/** \brief  Set 4k/64k page memory attributes

    The function sets 4k/64k page memory attributes

    \param [out]    descriptor_l2  L2 descriptor.
    \param [in]               mem  4k/64k page memory type: NORMAL, DEVICE, SHARED_DEVICE, NON_SHARED_DEVICE, STRONGLY_ORDERED
    \param [in]             outer  Outer cacheability: NON_CACHEABLE, WB_WA, WT, WB_NO_WA,
    \param [in]             inner  Inner cacheability: NON_CACHEABLE, WB_WA, WT, WB_NO_WA,

    \return          0  
 */
__STATIC_INLINE int __memory_page(uint32_t *descriptor_l2, mmu_memory_Type mem, mmu_cacheability_Type outer, mmu_cacheability_Type inner, mmu_region_size_Type page)
{
    *descriptor_l2 &= PAGE_4K_TEXCB_MASK;

    if (page == PAGE_64k)
    {
        //same as section
        __memory_section(descriptor_l2, mem, outer, inner);
    }
    else
    {
        if (STRONGLY_ORDERED == mem)
        {
            return 0;
        }
        else if (SHARED_DEVICE == mem)
        {
            *descriptor_l2 |= (1 << PAGE_4K_B_SHIFT);
        }
        else if (NON_SHARED_DEVICE == mem)
        {
             *descriptor_l2 |= (1 << PAGE_4K_TEX1_SHIFT);
        }
        else if (NORMAL == mem)
        {
            *descriptor_l2 |= 1 << PAGE_4K_TEX2_SHIFT;
            switch(inner)
            {
                case NON_CACHEABLE:
                break;
                case WB_WA:
                     *descriptor_l2 |= (1 << PAGE_4K_B_SHIFT);
                     break;
                case WT:
                    *descriptor_l2 |= 1 << PAGE_4K_C_SHIFT;
                     break;
                case WB_NO_WA:
                    *descriptor_l2 |= (1 << PAGE_4K_B_SHIFT) | (1 << PAGE_4K_C_SHIFT);
                    break;
            }
            switch(outer)
            {
                case NON_CACHEABLE:
                break;
                case WB_WA:
                      *descriptor_l2 |= (1 << PAGE_4K_TEX0_SHIFT);
                    break;
                case WT:
                     *descriptor_l2 |= 1 << PAGE_4K_TEX1_SHIFT;
                    break;
                case WB_NO_WA:
                    *descriptor_l2 |= (1 << PAGE_4K_TEX0_SHIFT) | (1 << PAGE_4K_TEX0_SHIFT);
                    break;
            }
        }
    }

    return 0;
}

/** \brief  Create a L1 section descriptor

    The function creates a section descriptor.
    
    Assumptions:
    - 16MB super sections not suported
    - TEX remap disabled, so memory type and attributes are described directly by bits in the descriptor
    - Functions always return 0

    \param [out]       descriptor  L1 descriptor
    \param [out]      descriptor2  L2 descriptor
    \param [in]               reg  Section attributes

    \return          0  
 */
__STATIC_INLINE int __get_section_descriptor(uint32_t *descriptor, mmu_region_attributes_Type reg)
{
    *descriptor  = 0;

   __memory_section(descriptor, reg.mem_t, reg.outer_norm_t, reg.inner_norm_t);
   __xn_section(descriptor,reg.xn_t);
   __domain_section(descriptor, reg.domain);
   __p_section(descriptor, reg.e_t);
   __ap_section(descriptor, reg.priv_t, reg.user_t, 1);
   __shared_section(descriptor,reg.sh_t);
   __global_section(descriptor,reg.g_t);
   __secure_section(descriptor,reg.sec_t);
   *descriptor &= SECTION_MASK;
   *descriptor |= SECTION_DESCRIPTOR;

   return 0;

}


/** \brief  Create a L1 and L2 4k/64k page descriptor

    The function creates a 4k/64k page descriptor.
    Assumptions:
    - TEX remap disabled, so memory type and attributes are described directly by bits in the descriptor
    - Functions always return 0

    \param [out]       descriptor  L1 descriptor
    \param [out]      descriptor2  L2 descriptor
    \param [in]               reg  4k/64k page attributes

    \return          0  
 */
__STATIC_INLINE int __get_page_descriptor(uint32_t *descriptor, uint32_t *descriptor2, mmu_region_attributes_Type reg)
{
    *descriptor  = 0;
    *descriptor2 = 0;

    switch (reg.rg_t)
    {
        case PAGE_4k:
            __memory_page(descriptor2, reg.mem_t, reg.outer_norm_t, reg.inner_norm_t, PAGE_4k);
            __xn_page(descriptor2, reg.xn_t, PAGE_4k);
            __domain_page(descriptor, reg.domain);
            __p_page(descriptor, reg.e_t);
            __ap_page(descriptor2, reg.priv_t, reg.user_t, 1);
            __shared_page(descriptor2,reg.sh_t);
            __global_page(descriptor2,reg.g_t);
            __secure_page(descriptor,reg.sec_t);
            *descriptor &= PAGE_L1_MASK;
            *descriptor |= PAGE_L1_DESCRIPTOR;
            *descriptor2 &= PAGE_L2_4K_MASK;
            *descriptor2 |= PAGE_L2_4K_DESC;
            break;

        case PAGE_64k:
            __memory_page(descriptor2, reg.mem_t, reg.outer_norm_t, reg.inner_norm_t, PAGE_64k);
            __xn_page(descriptor2, reg.xn_t, PAGE_64k);
            __domain_page(descriptor, reg.domain);
            __p_page(descriptor, reg.e_t);
            __ap_page(descriptor2, reg.priv_t, reg.user_t, 1);
            __shared_page(descriptor2,reg.sh_t);
            __global_page(descriptor2,reg.g_t);
            __secure_page(descriptor,reg.sec_t);
            *descriptor &= PAGE_L1_MASK;
            *descriptor |= PAGE_L1_DESCRIPTOR;
            *descriptor2 &= PAGE_L2_64K_MASK;
            *descriptor2 |= PAGE_L2_64K_DESC;
            break;

        case SECTION:
            //error
            break;    

    }

   return 0;

}

/** \brief  Create a 1MB Section

    \param [in]               ttb  Translation table base address
    \param [in]      base_address  Section base address
    \param [in]             count  Number of sections to create
    \param [in]     descriptor_l1  L1 descriptor (region attributes) 

 */
__STATIC_INLINE void __TTSection(uint32_t *ttb, uint32_t base_address, uint32_t count, uint32_t descriptor_l1)
{
    uint32_t offset;
    uint32_t entry;
    uint32_t i;

    offset = base_address >> 20;
    entry  = (base_address & 0xFFF00000) | descriptor_l1;

    //4 bytes aligned
    ttb = ttb + offset;

    for (i = 0; i < count; i++ )
    {
        //4 bytes aligned
       *ttb++ = entry;
       entry += OFFSET_1M;
    }
}

/** \brief  Create a 4k page entry

    \param [in]               ttb  L1 table base address
    \param [in]      base_address  4k base address
    \param [in]             count  Number of 4k pages to create
    \param [in]     descriptor_l1  L1 descriptor (region attributes) 
    \param [in]            ttb_l2  L2 table base address
    \param [in]     descriptor_l2  L2 descriptor (region attributes) 

 */
__STATIC_INLINE void __TTPage_4k(uint32_t *ttb, uint32_t base_address, uint32_t count, uint32_t descriptor_l1, uint32_t *ttb_l2, uint32_t descriptor_l2 )
{

    uint32_t offset, offset2;
    uint32_t entry, entry2;
    uint32_t i;


    offset = base_address >> 20;
    entry  = ((int)ttb_l2 & 0xFFFFFC00) | descriptor_l1;

    //4 bytes aligned
    ttb += offset;
    //create l1_entry
    *ttb = entry;

    offset2 = (base_address & 0xff000) >> 12;
    ttb_l2 += offset2;
    entry2 = (base_address & 0xFFFFF000) | descriptor_l2;
    for (i = 0; i < count; i++ )
    {
        //4 bytes aligned
       *ttb_l2++ = entry2;
       entry2 += OFFSET_4K;
    }
}

/** \brief  Create a 64k page entry

    \param [in]               ttb  L1 table base address
    \param [in]      base_address  64k base address
    \param [in]             count  Number of 64k pages to create
    \param [in]     descriptor_l1  L1 descriptor (region attributes) 
    \param [in]            ttb_l2  L2 table base address
    \param [in]     descriptor_l2  L2 descriptor (region attributes) 

 */
__STATIC_INLINE void __TTPage_64k(uint32_t *ttb, uint32_t base_address, uint32_t count, uint32_t descriptor_l1, uint32_t *ttb_l2, uint32_t descriptor_l2 )
{
    uint32_t offset, offset2;
    uint32_t entry, entry2;
    uint32_t i,j;


    offset = base_address >> 20;
    entry  = ((int)ttb_l2 & 0xFFFFFC00) | descriptor_l1;

    //4 bytes aligned
    ttb += offset;
    //create l1_entry
    *ttb = entry;

    offset2 = (base_address & 0xff000) >> 12;
    ttb_l2 += offset2;
    entry2 = (base_address & 0xFFFF0000) | descriptor_l2;
    for (i = 0; i < count; i++ )
    {
        //create 16 entries
        for (j = 0; j < 16; j++)
            //4 bytes aligned
            *ttb_l2++ = entry2;
        entry2 += OFFSET_64K;
    }
}

/*@} end of MMU_Functions */
#endif

#ifdef __cplusplus
}
#endif
