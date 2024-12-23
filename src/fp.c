/* place-holder for now */

#if 0

union I64F64 {
	i64 i64;
	f64 f64;
};

static f64 v64ttof64t(v64 v) {
	union I64F64 i64f64;
	i64f64.i64 = (i64)v;
	return i64f64.f64;
}

static v64 f64ttov64t(f64 v) {
	union I64F64 i64f64;
	i64f64.f64 = v;
	return (u64)i64f64.i64;
}

union I32F32 {
	i32 i32;
	f32 f32;
};

static f32 v64ttof32t(v64 v) {
	union I32F32 i32f32;
	i32f32.i32 = v64ttoi32t(v);
	return i32f32.f32;
}

/* 32-bit fp ALU results have hi bits set */
static v64 f32ttov64t(f32 v) {
	union I32F32 i32f32;
	i32f32.f32 = v;
	return (u64)(i32f32.i32 | 0xffffffff00000000ULL);
}

	f32 a0f32 = 0, a1f32 = 0, rf32 = 0;
	bool a0f32b = 0, a1f32b = 0, rf32b = 0;

	f64 a0f64 = 0, a1f64 = 0, rf64 = 0;
	bool a0f64b = 0, a1f64b = 0, rf64b = 0;

		case f32t: S(a1f32) = v64ttof32t(a1); break;
		case f64t: S(a1f64) = v64ttof64t(a1); break;

		case f32t: S(a0f32) = v64ttof32t(a0); break;
		case f64t: S(a0f64) = v64ttof64t(a0); break;

	case AOfadd32:    S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfsub32:    S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfrsub32:   S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfdiv32:    S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfrem32:    S(rf32) = V(a0f32) + V(a1f32); break;
	case AOfmul32:    S(rf32) = V(a0f32) + V(a1f32); break;

	case AOfadd64:    S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfsub64:    S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfrsub64:   S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfdiv64:    S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfrem64:    S(rf64) = V(a0f64) + V(a1f64); break;
	case AOfmul64:    S(rf64) = V(a0f64) + V(a1f64); break;

	case AOfneg32:    S(rf32) = -V(a0f32); break;
	case AOfneg64:    S(rf64) = -V(a0f64); break;

	case AOfceq32:    S(ri64) = (i64)(V(a0f32) == V(a1f32)); break;
	case AOfcge32:    S(ri64) = (i64)(V(a0f32) >= V(a1f32)); break;
	case AOfcgt32:    S(ri64) = (i64)(V(a0f32) >  V(a1f32)); break;
	case AOfcle32:    S(ri64) = (i64)(V(a0f32) <= V(a1f32)); break;
	case AOfclt32:    S(ri64) = (i64)(V(a0f32) <  V(a1f32)); break;
	case AOfcne32:    S(ri64) = (i64)(V(a0f32) != V(a1f32)); break;
	case AOfco32:     alu->err = AluNoImpl; break;
	case AOfcuo32:    alu->err = AluNoImpl; break;

	case AOfceq64:    S(ri64) = (i64)(V(a0f64) == V(a1f64)); break;
	case AOfcge64:    S(ri64) = (i64)(V(a0f64) >= V(a1f64)); break;
	case AOfcgt64:    S(ri64) = (i64)(V(a0f64) >  V(a1f64)); break;
	case AOfcle64:    S(ri64) = (i64)(V(a0f64) <= V(a1f64)); break;
	case AOfclt64:    S(ri64) = (i64)(V(a0f64) <  V(a1f64)); break;
	case AOfcne64:    S(ri64) = (i64)(V(a0f64) != V(a1f64)); break;
	case AOfco64:     alu->err = AluNoImpl; break;
	case AOfcuo64:    alu->err = AluNoImpl; break;

	case AOfext32:    S(rf64) = (f64)V(a0f32); break;
	case AOftrunc64:  S(rf32) = (f32)V(a0f64); break;

	case AOf32toi32:  S(ri32) = (i32)V(a0f32); break;
	case AOf32tou32:  S(ri32) = (i32)(u32)V(a0f32); break;
	case AOf32toi64:  S(ri64) = (i64)V(a0f32); break;
	case AOf32tou64:  S(ri64) = (i64)(u64)V(a0f32); break;
	case AOf64toi32:  S(ri32) = (i32)V(a0f64); break;
	case AOf64tou32:  S(ri32) = (i32)(u32)V(a0f64); break;
	case AOf64toi64:  S(ri64) = (i64)V(a0f64); break;
	case AOf64tou64:  S(ri64) = (i64)(u64)V(a0f64); break;

	case AOi32tof32:  S(rf32) = (f32)V(a0i32); break;
	case AOu32tof32:  S(rf32) = (f32)(u32)V(a0i32); break;
	case AOi64tof32:  S(rf32) = (f32)V(a0i64); break;
	case AOu64tof32:  S(rf32) = (f32)(u64)V(a0i64); break;
	case AOi32tof64:  S(rf64) = (f64)V(a0i32); break;
	case AOu32tof64:  S(rf64) = (f64)(u32)V(a0i32); break;
	case AOi64tof64:  S(rf64) = (f64)V(a0i64); break;
	case AOu64tof64:  S(rf64) = (f64)(u64)V(a0i64); break;

		case f32t: S(r) = f32ttov64t(V(rf32)); break;
		case f64t: S(r) = f64ttov64t(V(rf64)); break;
#endif /*0*/
