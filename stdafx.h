// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // »сключите редко используемые компоненты из заголовков Windows
// ‘айлы заголовков Windows:
#include <windows.h>
#include <winhttp.h>

#include <iostream>
#include <fstream>
#include <string>

#include <boost/cast.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/serialization/singleton.hpp>
#include "TrideHelper.h"

// TODO. ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
