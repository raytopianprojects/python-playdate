# TODO
# Callback parsing
# Generate enums
# Make sure keywords (like while) are treated as types
# Generate doc strings
# the return type doesnt always exist which can cause parsing errors
# to prevent incomple struct type errors the type on the left must be a pointer
# lvol and rvol need to have float added before them
# enums should be treated as ints
# midinote is a float
def type_convert(_type):
    match _type:
        case "void":
            py_type = "none"
        case "float":
            py_type = "float"
        case "int":
            py_type = "int"
        case _:
            py_type = "object"
    return py_type

pd = []
pd_f = []
pd_f_add = []
funcs = []
funcs_f = []
structs = []
structs_f = []
types = set()
types_d = set()
enums = set()

ignore_list = ("")

with open("docs" , encoding='utf-8') as f:
    lines = f.readlines()
    for l in lines:

        if "playdate->" in l and "()." not in l and  "() t" not in l and "() a" not in l and " and " not in l and "() but " not in l and "return" not in l:
            pd.append(l.replace(", rows)", ", int rows)"))
        elif l.lstrip().startswith("k") and ":" not in l:
            a_enum = l.lstrip().rstrip().replace(",", "").split("=")[0]
            if a_enum not in ("kSpriteCollisionTypeSlide", "kSpriteCollisionTypeBounce", "kSpriteCollisionTypeFreeze", "kSpriteCollisionTypeOverlap"):
                enums.add(f"ADD_ENUM({a_enum});")

print(pd, funcs, structs)

pd_template_func_0 = """static bool py_@name(int argc, py_Ref argv) {
    PY_CHECK_ARGC(@args);
    @type_check
    @call
    py_new@type(py_retval()@value);
    return true;
}"""
struct_types = ("LCBitmap", "LCBitmap*", "luaL_Reg", "synthCopyUserdataFunc", "RingMoOverdrivedulator", "writeFunc", "SDFile_readud", "AudioInputFunction", "SoundSource_synth", "SDFile_userdata")

for x in pd:
    x = x.rstrip()
    args = x.split(",")
    args[0] = args[0].split("(")[-1]
    args[-1] = args[-1].split(")")[0]
    args = [x for x in args if x.strip()]
    arg_count = len(args)

    type_checks = ""
    type_checks_list = []
    ref = []
    if arg_count > 0:
        for y in range(arg_count):
            _type_parse  = args[y].rstrip().lstrip().split(' ')
            _type = _type_parse[0].replace("&", "").replace("*)", "_").replace(")", "").replace(" ", "_")
            if _type in ("...", "while") or (arg_count == 1 and _type == "void"):
                arg_count -= 1
                continue
            if _type in ["struct", "const", "unsigned"]:
                _type += " " + _type_parse[1]
                py_type = "py_to" + _type_parse[1].replace("*", "").replace("char", "str")
            elif _type == "enum":
                _type = _type_parse[1]
                py_type = "py_to" + _type_parse[1].replace("*", "").replace("char", "str")
            else:
                py_type = "py_to" + _type.replace('*', '')

            o_type = _type
            _type  = _type.replace("*", "")
            print("TYPE", _type,  _type_parse, _type not in ["int", "float", "char", "void", "while", "const char", "unsigned int", "const void", "0", "...", "int32_t", "size_t", "int_16", "uint8_t"])
            pointer = ""
            if _type not in ["int", "float", "char", "void", "while", "const char", "unsigned int", "const void", "0", "...", "int32_t", "size_t", "int_16", "uint8_t"]:
                n_type = _type.replace(" ", "_")
                struct = ""
                if _type in struct_types or "PDDateTime" in _type or "luaL_Reg" in _type:
                    struct = "struct"
                py_type = f"({struct} {_type.split()[-1]}*)py_touserdata"

                pointer = "*"
                if n_type not in ("str", "int", "float"):
                    types.add(f'py_Type {n_type}_type = py_newtype("{n_type}", tp_object, mod, NULL);')
                    types_d.add(f"static py_Type tp_{n_type};")
            s_type = _type
            if _type != "void" and _type != "const void":
                if _type in ["uint32_t", "int16_t", "uint8_t", "unsigned int", "size_t", "uint8_t*", "int32_t"]:
                    _type = "int"
                    py_type = "py_toint"
                elif _type in ("MIDINote", ):
                    print("MIDINOTE")
                    s_type = "float"
                    _type = "float"
                    py_type = "py_tofloat"
                    pointer = ""
                    if "MIDINote*" in _type_parse:
                        print("MIDINOTE*")
                        pointer = ""
                        s_type = "float*"
                        _type = "float*"
                        py_type = "(float*)py_touserdata"

                elif _type in struct_types or ("PDDateTime" in _type and "struct" not in _type) or "luaL_Reg" in _type:
                    s_type = "struct " + _type

                if "float*" in _type_parse:
                    ref.append("&")
                elif "float" in _type_parse and any("*" in temp_type for temp_type in _type_parse):
                    ref.append("")
                    pointer = "*"
                    py_type = "py_touserdata"
                elif "LCDPolygonFillRule" in _type_parse or "PDPeripherals" in _type_parse or "LFOType" in _type_parse or "PDRect" in _type_parse or "LCDRect" in _type_parse or "json_reader" in _type_parse or "LCDBitmapFlip" in _type_parse or "LCDBitmapDrawMode" in _type_parse or "FileOptions" in _type_parse or "LCDLineCapStyle" in _type_parse or "PDStringEncoding" in _type_parse or "SoundFormat" in _type_parse or "SoundWaveform" in _type_parse or "TwoPoleFilterType" in _type_parse:
                    ref.append("*")
                else:
                    ref.append("")

                if "LCDVideoPlayer" in _type_parse:
                    pointer = "*"

                if "MicSource" in _type_parse or "PDTextWrappingMode" in _type_parse or "PDTextAlignment" in _type:
                    _type = "int"
                    s_type = "int"
                    pointer = ""
                    py_type = "py_toint"

                type_checks_list.append(f"PY_CHECK_ARG_TYPE({y}, tp_{_type.replace(' ', '_').replace('*', '').replace('const_char', 'str').replace('char', 'str')});\n    "
                                        f"{s_type}{pointer} _{y} = {py_type.replace('char', 'str')}(py_arg({y}));")
            else:
                ref.append("")
                print("OTYPE", _type_parse, o_type)

                commnect = ""
                if pointer == "":
                    type_checks_list.append(
                        f"void* _{y} = py_touserdata(py_arg({y})); // This is a callback function, this will not work but allows for compling")
                else:
                    type_checks_list.append(f"{commnect}{o_type}{pointer} _{y} = {py_type.replace('*', '')}(py_arg({y}));")

        type_checks = "\n".join(type_checks_list)

    r_type, func = x.split(" ", 1)
    if not r_type.lstrip().startswith("playdate->"):
        if not x.split(" ")[1].startswith("playdate->"):
            r_type += " " + x.split(" ")[1]
            i = 0
            while not func.startswith("playdate->"):
                func =  x.split(" ")[i]
                i += 1
        if "->" in r_type:
            func = r_type
        func = func.replace("playdate->", "py_pd->")
        if arg_count > 0:
            func = func.split("(")[0]
            func += "("
            for y in range(arg_count):
                if y + 1 == arg_count:
                    func += f"{ref[y]}_{y});"
                    break
                func += f"{ref[y]}_{y},"
        else:
            if func[-1] != ";":
                func += ";"
        r_type = r_type.replace("LCBitmap", "struct LCBitmap")
        string = pd_template_func_0.replace("@args", str(arg_count)).replace("@type_check", type_checks)
        py_type = type_convert(r_type)
        if py_type == "object":
            string = string.replace("@value", f"@value, 0, sizeof({r_type})")

        if arg_count == 0:
            func = func.replace("void", "")


        if r_type != "void":
            string = string.replace("@call", f"{r_type} r_type = {func}").replace("@value", ", r_type")
        else:
            string = string.replace("@call", func).replace("@value", "")

        _name = func.split("->")
        _name[-1] = _name[-1].split("(")[0]
        print(_name)
        name = "_".join(_name[1:])
        ignore_funcs = []
        ignore_funcs  = ("sound_sample_newSampleFromData", "sound_fileplayer_fadeVolume", "system_realloc", "graphics_setBackgroundColor", "sound_getHeadphoneState", "sound_lfo_setFunction", "file_listfiles", "sound_effect_ringmodulator_freeRingmod", "lua_registerClass_deprecated",
                         "sound_source_setCompletionCallback", "sound_sample_decompress", "graphics_drawTextInRect",
                         "sound_synth_getVolume", "system_clearICache", "sprite_getCollideRect", "sprite_getBounds")
        if name in ignore_funcs:
            string = f"// The function {name} will needs extra work to work"
        else:
            pd_f_add.append(f'py_bindfunc(mod, "{"_".join(_name[1:])}", &py_{name});\n')

            string = string.replace("@type", py_type).replace("@name", name).replace("[[f-sound.effect.ringmodulator.freeRingmod] .", "").replace("const luaL_Reg", "luaL_Reg").replace(" LCDVideoPlayer ", " LCDVideoPlayer*").replace("(LCDVideoPlayer)", "(LCDVideoPlayer*)")
            pd_f.append(string + "\n")

            print(string, r_type)

with open("t.c", "w") as f:
    f.write("""#include "pd_api.h"
#include "pocketpy.h"
#include "string.h"
PlaydateAPI* py_pd = NULL;

static void py_add_types(py_GlobalRef mod);
void py_add_funcs(py_GlobalRef mod);
void py_add_enums(py_GlobalRef mod);
void python_playdate(PlaydateAPI* pdapi){
    py_pd = pdapi;
    py_GlobalRef play_mod = py_newmodule("playdate");
    py_add_types(play_mod);
    py_add_funcs(play_mod);
    py_add_enums(play_mod);
}
""")

    f.write("\n#define ADD_ENUM(name) py_newint(py_emplacedict(mod, py_name(#name)), name)\n")
    f.write("\n\n")
    f.write("\n".join(types_d))
    f.write("\nvoid py_add_types(py_GlobalRef mod){\n")
    f.write("\n".join(types))
    f.write("\n}\n\n")
    f.writelines(pd_f)
    f.write("\nvoid py_add_funcs(py_GlobalRef mod){\n")
    f.write("    ".join(pd_f_add))
    f.write("}\n")
    f.write("\nvoid py_add_enums(py_GlobalRef mod){\n")
    f.write("\n".join(enums))
    f.write("\n}\n")


print(types_d, types, enums)