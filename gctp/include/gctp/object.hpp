#ifndef _GCTP_OBJECT_HPP_
#define _GCTP_OBJECT_HPP_
#include <gctp/config.hpp>
#ifdef GCTP_ONCE
#pragma once
#endif // GCTP_ONCE
/** @file
 * GameCatapult オブジェクトスーパークラスヘッダファイル
 *
 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
 * @date 2004/02/09 23:00:42
 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
 */
#include <gctp/typeinfo.hpp>
#include <gctp/def.hpp>
#include <gctp/mutex.hpp>
#include <memory>

namespace gctp {

	class Ptr;
	class Hndl;
	class Serializer;
	namespace detail {
		class Stub;
	}

	/** GameCatapult 削除アルゴリズム指定基底
	 *
	 * gctp::Pointerが、このオブジェクトを削除する方法を知るために必要な情報を提供する
	 *
	 * 通常、もちろんdeleteである。
	 */
	class AbstractDeleter {
	public:
		/** 明示的にデストラクタを呼ぶ
		 *
		 * Deleter定義のためのユーティリティー
		 */
		static void destroy(class Object *);
		/** 領域開放処理
		 *
		 * これを再定義し、カスタムのメモリ確保に対応する
		 * @code
	// 典型的な定義
	virtual void operator()(class Object *p) const
	{
		destroy(p); // デストラクタを呼び出し
		alloca().deallocate(p); // 開放処理
	}
         * @endcode
		 */
		virtual void operator()(class Object *) const = 0;
		/// ヌルデリータ定義用の宣言
		static void nulldelete(class Object *) {}
	};

	/// デリーター定義を簡略化するテンプレート
	template<void (_Func)(class Object *)>
	class Deleter : public AbstractDeleter {
	public:
		virtual void operator()(class Object *p) const
		{
			_Func(p);
		}
		static AbstractDeleter *get()
		{
			static Deleter me;
			return &me;
		}
	private:
		Deleter() {}
	};
	
	/// 何もしないデリータ
	typedef Deleter<AbstractDeleter::nulldelete> NullDeleter;

	/// STL準拠のアロケータからDeleterを定義
	template<class Allocator>
	class DeleterAdaptor : public AbstractDeleter {
	public:
		virtual void operator()(class Object *p) const
		{
			destroy(p);
			Allocator().deallocate(p);
		}
		static AbstractDeleter *get()
		{
			static DeleterAdaptor me;
			return &me;
		}
	private:
		DeleterAdaptor() {}
	};

	/** GameCatapult オブジェクトスーパークラス
	 *
	 * 参照カウンタ・シリアライズ・プロパティーを提供する。
	 *
	 * gctp::Pointer / gctp::Handle で指すオブジェクトはすべてこのクラスの派生である必要がある｡
	 *
	 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
	 * @date 2004/02/09 23:02:30
	 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
	 */
	class Object {
	public:
		/// 参照カウンタの値
		uint count() const { AutoLock al(mutex_); return refcount_; }
		/// 共有されていないか？(trueなら参照カウンタが１)
		bool unique() const { AutoLock al(mutex_); return (refcount_==1)? true : false; }

		/** 非同期処理への対応をon/off
		 *
		 * 通常オフ。
		 *
		 * これがオンだと、そのオブジェクトは参照カウンタの上下、Stubの参照カウンタの上下
		 * の際に排他制御をするようになり、マルチスレッドの状況下でも安全にPointer/Handleを
		 * 運用できるようになる。
		 *
		 * 複数のスレッドから参照される期間が過ぎたのなら、効率のためにも再びオフにするとよい。
		 *
		 * またObject派生オブジェクトをコピーした場合、同期処理属性も引き継がれる。\n
		 * synchronizeを呼び出したことが無いオブジェクトでもコピー元で呼び出されていた場合
		 * Mutexオブジェクトが製作される点に注意。
		 *
		 * @param yes 排他制御を行うか？
		 * @return 以前の設定値
		 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
		 * @date 2004/12/03 14:49:11
		 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
		 */
		void synchronize(bool yes);

		/** Pointer確保を抑止
		 *
		 * スタック上に確保されたり、他のオブジェクトのメンバとして確保されるObject派生オブジェクト
		 * に対してこれを呼び出すと、Handleは確保できてもPointerは確保できないようにできる。
		 *
		 * @author SAM (T&GG, Org.)<sowwa_NO_SPAM_THANKS@water.sannet.ne.jp>
		 * @date 2004/12/03 14:49:11
		 * Copyright (C) 2001,2002,2003,2004 SAM (T&GG, Org.). All rights reserved.
		 */
		void deleteGuard() { refcount_ = -1; }

		/** デリーターを設定
		 *
		 * 通常のdelete演算子で削除されるのが好ましくない場合、gctp::Deleterの派生を定義して
		 * それを与える。
		 */
		void setDeleter(AbstractDeleter *deleter)
		{
			deleter_ = deleter;
		}

		/** デリーターを取得
		 *
		 */
		AbstractDeleter *getDeleter() const
		{
			return deleter_;
		}

		/// gctp::Object用のdelete処理
		static void destroy(Object *obj)
		{
			if(obj->deleter_) (*obj->deleter_)(obj);
			else delete obj;
		}
		
#ifndef GCTP_USE_STD_RTTI
		/// gctp::Objectのgctp::TypeInfo
		static const gctp::TypeInfo &typeinfo() { static gctp::TypeInfo typeinfo("Object", NULL); return typeinfo; }
		/// このオブジェクトの最も派生が進んだgctp::TypeInfoを返す
		virtual const gctp::TypeInfo &typeOfThis() const { return typeinfo(); }
#endif

		/// Objectの各メンバはインスタンス毎に独立なのでコピーさせない
		Object & operator=(const Object &src)
		{
			// ただし同期処理属性だけは引き継ぐ
			if(src.mutex_) synchronize(true);
			return *this;
		}

		/// シリアライズ
		virtual void serialize(Serializer &) {}

# ifdef GCTP_USE_STD_RTTI
		/// プロパティー
		class Property property(const char *property_name);
		/// プロパティーメソッド呼び出し
		bool method(const char *method_name);
# endif
# ifdef GCTP_USE_DYNAMIC_PROPERTY
		/// 実行時プロパティー取得
		class DynamicPropertyMap *dynamicProperty() { return dynamic_property_; }
		/// 実行時プロパティー設定
		void setDynamicProperty(class DynamicPropertyMap *dpmap);
# endif
	protected:
		/// デフォルトコンストラクタ
		Object() : refcount_(0), stub_(0), deleter_(0), mutex_(0)
# ifdef GCTP_USE_DYNAMIC_PROPERTY
			, dynamic_property_(0)
# endif
		{}
		/// Objectの各メンバはインスタンス毎に独立なのでコピーさせない
		Object(const Object &src) : refcount_(0), stub_(0), deleter_(0), mutex_(0)
# ifdef GCTP_USE_DYNAMIC_PROPERTY
			, dynamic_property_(0)
# endif
		{
			// ただし同期処理属性だけは引き継ぐ
			if(src.mutex_) synchronize(true);
		}
		virtual ~Object();

		/** 標準のメモリ確保関数
		 *
		 * Factory定義のマクロ内で、create関数定義の際に参照される。
		 *
		 * ユーザーがgctp::Objectの派生クラスにおいて置き換えるには、
		 * 派生クラス内で同じシグネチャを持つ関数を宣言するだけでよい。
		 */
		static void *allocate(std::size_t n) { return ::operator new(n); }

		/** 標準のDeleter
		 *
		 * Factory定義のマクロ内で、create関数定義の際に参照される。
		 *
		 * ユーザーがgctp::Objectの派生クラスにおいて置き換えるには、
		 * 派生クラス内で同じシグネチャを持つ関数を宣言するだけでよい。
		 */
		static AbstractDeleter *deleter() { return 0; }

		/** 現在流通しているハンドルを破棄
		 *
		 */
		void expire() const;

	private:
		friend class Ptr;
		friend class Hndl;
		friend class detail::Stub;
		friend class AbstractDeleter;
		mutable int refcount_;
		bool addRef() const { AutoLock al(mutex_); if(refcount_ >= 0) { ++refcount_; return true; } else return false; }
		bool decRef() const { AutoLock al(mutex_); if(refcount_ > 0 && --refcount_ == 0){ refcount_=-1; expire(); return true; } else return false; }
		mutable detail::Stub *stub_;
		AbstractDeleter *deleter_;
		class AutoLock {
		public:
			AutoLock(Mutex *mutex) : mutex_(mutex) { if(mutex_) mutex_->lock(); }
			~AutoLock() { if(mutex_) mutex_->unlock(); }
		private:
			Mutex *mutex_;
		};
		mutable Mutex *mutex_;
# ifdef GCTP_USE_DYNAMIC_PROPERTY
		class DynamicPropertyMap *dynamic_property_;
# endif
	};

} // namespace gctp

#endif //_GCTP_OBJECT_HPP_