// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
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

// TODO. ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
