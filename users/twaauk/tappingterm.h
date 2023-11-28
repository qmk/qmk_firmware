#ifndef TAPPINGTERM_H
#define TAPPINGTERM_H
#define TAPPING_TERM_MIN_ALT 200
#define TAPPING_TERM_MIN_SHIFT 150
#define TAPPING_TERM_MIN_LAYER 170
#define TAPPING_TERM_MIN_CTRL 150

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record)
{
	// この時間押し続けているとhold側のキーとなる
	switch (keycode)
	{

	case VKC_SA:
	case VKC_SZ:
	case VKC_SET:
	case VKC_SSP:

	case VKC_S6:
#if VKC_S6 != VKC_SCIR
	case VKC_SCIR:
#endif
	case VKC_SF10:
	case VKC_STB:
	case VKC_SF12:
		return TAPPING_TERM_MIN_SHIFT;

	case VKC_1N:
	case VKC_2B:
	case VKC_3M:
	case VKC_4V:
	case VKC_1J:
	case VKC_2F:
		return TAPPING_TERM_MIN_LAYER;

	case VKC_AD:
	case VKC_AK:
		return TAPPING_TERM_MIN_ALT;

	case VKC_CS:
	case VKC_CL:
		return TAPPING_TERM_MIN_CTRL;
	}

	return TAPPING_TERM;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t* record)
{
	// true ... get_tapping_term()の値は関係なしに、同時押しがあったら確定でホールド扱いにする

	return false;
}

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t* record)
{
	// true ... get_permissive_hold()==trueの場合、同時押しの時間がget_tapping_term()を越えるまではホールド扱いにしない
	// つまり、get_permissive_hold()==falseなら、単体キーのみ監視で、そのキーをget_tapping_term()以上押していたらホールドになる
	// get_permissive_hold()==trueでget_ignore_mod_tap_interrupt()==falseなら、同時押しが発生した瞬間ホールドになる
	// get_permissive_hold()==trueでget_ignore_mod_tap_interrupt()==trueなら、同時押しからget_tapping_term()経過してからホールドになる

	return false;
}
#endif
