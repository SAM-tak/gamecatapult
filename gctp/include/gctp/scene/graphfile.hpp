#ifndef _GCTP_SCENE_GRAPHFILE_HPP_
#define _GCTP_SCENE_GRAPHFILE_HPP_
/** @file
 * GameCatapult シーングラフコンテントファイルクラス
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/02/04 21:29:23
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#include <gctp/class.hpp>
#include <gctp/buffwd.hpp> // for BufferPtr
#include <gctp/pointerlist.hpp>
#include <gctp/dxcomptrs.hpp>
#include <map>

namespace gctp { namespace scene {

	typedef Ptr (*XFileHandleMethod)(PtrList pvector, const char *extra_name);
	/** Ｘファイルハンドラー登録クラス
	 *
	 * テンプレートＩＤ(GUID)→ハンドラーのＤＢを構成する。
	 *
	 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
	 * @date 2004/02/08 11:17:33
	 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
	 */
	class XFileHandler {
	public:
		XFileHandler(const GUID &template_id, const XFileHandleMethod f);
		~XFileHandler();

		static bool hasHandler(const GUID &template_id);
		static XFileHandleMethod get(const GUID &template_id);

	private:
		typedef std::map<GUID, XFileHandleMethod> HandlerMap;
		HandlerMap::iterator me_;
		static HandlerMap &handlers();
	};

	/** シーングラフファイル読み込み
	 *
	 * ファイルを読みこんで、内部のデータをリソースとして登録していく。\n
	 * 登録されたリソースはこのファイルリソースによって所有され、
	 * このリソースの開放によって、読みこんだリソースを開放する。
	 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
	 * @date 2004/01/29 15:07:29
	 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
	 */
	class GraphFile : public Object, public PtrList {
	public:
		/// XFileの読みこみ
		bool setUpFromX(const _TCHAR *fn);
		/// XFileの読みこみ
		bool setUpFromX(BufferPtr buffer);
		/// (コリジョンファイルとして)XFileの読みこみ
		bool setUpAsColFromX(BufferPtr buffer);
		
		static void setCustomSkinnedShaderBrush(const char *classname);
		static void setCustomSkinnedShaderBrush(const GCTP_TYPEINFO *typeinfo)
		{
			custom_skinned_shader_brush_typeinfo__ = typeinfo;
		}
		static const GCTP_TYPEINFO *getCustomSkinnedShaderBrush()
		{
			return custom_skinned_shader_brush_typeinfo__;
		}
		static void setCustomSolidShaderBrush(const char *classname);
		static void setCustomSolidShaderBrush(const GCTP_TYPEINFO *typeinfo)
		{
			custom_solid_shader_brush_typeinfo__ = typeinfo;
		}
		static const GCTP_TYPEINFO *getCustomSolidShaderBrush()
		{
			return custom_solid_shader_brush_typeinfo__;
		}

	protected:
		bool LuaCtor(luapp::Stack &L);
		int get(luapp::Stack &L);
		int size(luapp::Stack &L);
		int ipairs(luapp::Stack &L);
		void printHierarchy(luapp::Stack &L);
		static int setCustomSkinnedShaderBrush(luapp::Stack &L);
		static int getCustomSkinnedShaderBrush(luapp::Stack &L);
		static int setCustomSolidShaderBrush(luapp::Stack &L);
		static int getCustomSolidShaderBrush(luapp::Stack &L);

	private:
		struct LuaIPair {
			int n;
			PtrList *list;
			PtrList::iterator i;
		};
		static int _ipair_next(lua_State *l);
		static int _ipair_gc(lua_State *l);

		static const GCTP_TYPEINFO *custom_skinned_shader_brush_typeinfo__; // とりあえず。。。
		static const GCTP_TYPEINFO *custom_solid_shader_brush_typeinfo__; // とりあえず。。。
		GCTP_DECLARE_CLASS;
		TUKI_DECLARE(GraphFile);
	};

}} //namespace gctp::scene

/** Ｘファイル読み込みハンドラ登録マクロ
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/02/08 11:18:01
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#define GCTP_REGISTER_XFILE_HANDLER(_TID, _M)				\
	Ptr _TID##_handler(XData *cur) {						\
		Handle<_T> h = db()[name];							\
		if(h) return h.lock();								\
		Pointer<_T> ret = Object::create(GCTPTYPEID(_T));	\
		if(ret) {											\
			ret->setUp(name);								\
			db().insert(Hndl(ret.get()), name);				\
		}													\
		return ret;											\
	}														\
	XFileHandler _TID##_handler_reg(_TID, _TID##_handler)

#endif //_GCTP_SCENE_GRAPHFILE_HPP_