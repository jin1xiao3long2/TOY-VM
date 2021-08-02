#pragma once

#include<cstdint>

namespace csvm {
	struct var_type_t {
		std::uint16_t extend_type = 0;
		std::uint8_t building_type = 0;

		var_type_t(std::uint32_t t)
		{
			building_type = (t & 0x000000ff);
			extend_type = (t & 0x00ffff00) >> 8;
		}
	};

	struct var_t {
		std::uint8_t life_cycle = 0; // life_cycle undefined
		csvm::var_type_t type_tag;

//		union data_t {
//			std::uint32_t ui32 = 0;
//			std::vector<std::uint32_t> *ptr_vec_ui32;
//
//			explicit data_t(std::uint32_t ui32) : ui32(ui32) {}
//
//			explicit data_t(std::vector<std::uint32_t> *ptr) {
//				ptr_vec_ui32 = ptr;
//			}
//		} data;
        std::uint32_t data;
		static csvm::var_type_t get_unified_type(var_t l, var_t r)
		{
			if (l.type_tag.extend_type != 0 || r.type_tag.extend_type != 0)
				throw std::logic_error("extend_type not implemented yet.");
			if (l.type_tag.building_type > r.type_tag.building_type)
				std::swap(l, r);
			switch (l.type_tag.building_type) {
			case 0x01:
				switch (r.type_tag.building_type) {
				case 0x01:
					return {0x01};
				case 0x02:
					return {0x02};
				}
			case 0x02: {
				switch (r.type_tag.building_type) {
				case 0x02:
					return {0x02};
				}
			}
			default:
				throw std::logic_error("extend_type not implemented yet.");
			}
		}

		bool operator > (int r){
		    switch(type_tag.building_type){
		        case 1:
		            return reinterpret_cast<int &>(data) > r;
		        case 2:
                    return reinterpret_cast<float &>(data) > r;
		    }
		}

		bool operator == (int r){
            switch(type_tag.building_type){
                case 1:
                    return reinterpret_cast<int &>(data) == r;
                case 2:
                    return reinterpret_cast<float &>(data) == r;
            }
		}

		var_t operator +=(const var_t &o)
        {
            if (this->type_tag.extend_type == 0) {
                switch(this->type_tag.building_type) {
                    case 0x1:
                        switch (o.type_tag.building_type) {
                            case 0x1:
                                this->data += o.data;
                            break;
                            case 0x2: {
                                float res = float(this->data) + reinterpret_cast<const float &>(o.data);
                                this->data = reinterpret_cast<const std::uint32_t &>(res);
                                this->type_tag = {0x00000002};
                            }
                            break;
                        }
                    break;

                    case 0x2:
                        switch (o.type_tag.building_type) {
                            case 0x1: {
                                float res = reinterpret_cast<float &>(this->data) + float(o.data);
                                this->data = reinterpret_cast<const std::uint32_t &>(res);
                            }
                            break;
                            case 0x2:
                                reinterpret_cast<float &>(this->data) += reinterpret_cast<const float &>(o.data);
                            break;
                        }
                    break;
                }
                return *this;
            }
            throw std::logic_error("extend_type not implemented yet.");
        }


        var_t operator -=(const var_t &o)
        {
            if (this->type_tag.extend_type == 0) {
                switch(this->type_tag.building_type) {
                    case 0x1:
                        switch (o.type_tag.building_type) {
                            case 0x1:
                                 this->data -= o.data;
                            break;
                            case 0x2: {
                                float res = float(this->data) - reinterpret_cast<const float &>(o.data);
                                this->data = reinterpret_cast<const std::uint32_t &>(res);
                                this->type_tag = {0x00000002};
                            }
                            break;
                        }
                    break;

                    case 0x2:
                        switch (o.type_tag.building_type) {
                            case 0x1: {
                                float res = reinterpret_cast<float &>(this->data) - float(o.data);
                                this->data = reinterpret_cast<const std::uint32_t &>(res);
                            }
                            break;
                            case 0x2:
                                reinterpret_cast<float &>(this->data) -= reinterpret_cast<const float &>(o.data);
                            break;
                        }
                    break;
                }
                return *this;
            }
            throw std::logic_error("extend_type not implemented yet.");
        }


        var_t operator *=(const var_t &o)
        {
            if (this->type_tag.extend_type == 0) {
                switch(this->type_tag.building_type) {
                    case 0x1:
                        switch (o.type_tag.building_type) {
                            case 0x1:
                                this->data *= o.data;
                            break;
                            case 0x2: {
                                float res = float(this->data) * reinterpret_cast<const float &>(o.data);
                                this->data = reinterpret_cast<const std::uint32_t &>(res);
                                this->type_tag = {0x00000002};
                            }
                            break;
                        }
                    break;

                    case 0x2:
                        switch (o.type_tag.building_type) {
                            case 0x1: {
                                float res = reinterpret_cast<float &>(this->data) * float(o.data);
                                this->data = reinterpret_cast<const std::uint32_t &>(res);
                            }
                            break;
                            case 0x2:
                                reinterpret_cast<float &>(this->data) *= reinterpret_cast<const float &>(o.data);
                            break;
                        }
                    break;
                }
                return *this;
            }
            throw std::logic_error("extend_type not implemented yet.");
        }

		var_t operator /=(const var_t &o)
		{
			if (this->type_tag.extend_type == 0) {
			    switch(this->type_tag.building_type) {
			        case 0x1:
                    switch (o.type_tag.building_type) {
                        case 0x1:
                            this->data /= o.data;
                        break;
                        case 0x2: {
                            float res = float(this->data) / reinterpret_cast<const float &>(o.data);
                            this->data = reinterpret_cast<const std::uint32_t &>(res);
                            this->type_tag = {0x00000002};
                        }
                        break;
                    }
                    break;

                    case 0x2:
                    switch (o.type_tag.building_type) {
                        case 0x1: {
                            float res = reinterpret_cast<float &>(this->data) / float(o.data);
                            this->data = reinterpret_cast<std::uint32_t &>(res);
                        }
                        break;
                        case 0x2:
                            reinterpret_cast<float &>(this->data) /= reinterpret_cast<const float &>(o.data);
                        break;
                    }
                    break;
                }
                return *this;
			}
			throw std::logic_error("extend_type not implemented yet.");
		}

		explicit var_t(csvm::var_type_t type_tag, std::uint32_t ui32_data)
			: type_tag(type_tag), data(ui32_data)
		{
		}

//		explicit var_t(csvm::var_type_t type_tag, std::vector<std::uint32_t> *ptr_data)
//			: type_tag(type_tag), data(ptr_data)
//		{
//		}

		explicit var_t(std::uint32_t ui32_life_and_type_tag, std::uint32_t ui32_data)
			: type_tag(ui32_life_and_type_tag & 0x00ffffff), data(ui32_data),
			  life_cycle((ui32_life_and_type_tag & 0xff000000) >> 24)
		{
		}

//		explicit var_t(std::uint32_t ui32_life_and_type_tag, std::vector<std::uint32_t> *ptr_data)
//			: type_tag(ui32_life_and_type_tag & 0x00ffffff), data(ptr_data),
//			  life_cycle((ui32_life_and_type_tag & 0xff000000) >> 24)
//		{
//		}
	};
}