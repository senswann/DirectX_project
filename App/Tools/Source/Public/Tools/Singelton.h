#pragma once
#include <memory>

namespace Tools {
	template<class TClassType>
	class Singelton {
	public:
		Singelton(const Singelton&) = delete;
		Singelton operator=(const Singelton&) = delete;

		inline static TClassType& Get() {
			static TClassType instance;
			return instance;
		}
	protected:
		inline Singelton() {};
	};
}